#include "game.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <sys/_types/_ssize_t.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "constants/game_constants.h"
#include "core/window.h"
#include "entities/actions/player_input_handler.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "graphics/renderer.h"
#include "graphics/sprite.h"
#include "network/packet.h"
#include "ui/hud.h"
#include "util/logger.h"
#include "world/map.h"

namespace {

bool IsBehindHouse(Sprite::Coordinate coordinate) {
  const int house_x_position = 670;
  const int house_y_position = 200;
  return coordinate.y_pos <= house_y_position &&
         coordinate.x_pos <= house_x_position;
}

}  // anonymous namespace

SDL_Event Game::event_;

Game::Game() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    window_ = std::make_unique<Window>(
        "RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        Constants::WINDOW_SIZE, Constants::WINDOW_SIZE);
    renderer_ = std::make_unique<Renderer>(window_->GetSDLWindow());
    is_running_ = true;
    Logger::Debug("Game", "Initialized SDL");
  } else {
    Logger::Error("Game", "Failed to initialize SDL");
    is_running_ = false;
    return;
  }

  player_ = std::make_unique<Player>();
  Logger::Debug("Game", "Player character created");

  map_ = std::make_unique<Map>();
  Logger::Debug("Game", "Map created");

  hud_ = std::make_unique<HUD>();
  Logger::Debug("Game", "HUD created");

  client_ = Client::Create("127.0.0.1", "8080");
  if (client_ != nullptr) {
    Logger::Debug("Game", "Client created");
  }
}

Game::~Game() {
  SDL_Quit();
  Logger::Debug("Game", "Game destroyed");
}

void Game::Render() {
  SDL_RenderClear(Renderer::renderer_);
  // Order of rendering matters: first rendered = back, last rendered = front.
  map_->RenderGrassDirt();
  map_->RenderGrassWater();
  map_->RenderWaterfall();
  map_->RenderCliff();
  map_->RenderPlants();
  map_->RenderClothingRack();

  const bool player_behind =
      player_->IsBehindFence() || IsBehindHouse(player_->GetCoordinate());

  // Render characters that should appear behind fence/house
  if (player_behind) {
    player_->Render();
  }

  map_->RenderWoodFence();
  map_->RenderHouse();
  map_->RenderMailbox();

  // Render characters that should appear in front of fence/house
  if (!player_behind) {
    player_->Render();
  }

  hud_->RenderHotBar();

  // Render other players.
  for (const auto& [_, other_player] : others_players_) {
    other_player->Render();
  }

  SDL_RenderPresent(Renderer::renderer_);  // Double buffering
}

void Game::Update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      is_running_ = false;
    }
  }
  InputHandler::HandleInput(*player_, *hud_);

  std::array<Packet, Constants::MAX_PLAYERS> packets{};
  const ssize_t bytes_received =
      client_->Receive(packets.data(), sizeof(packets));
  if (bytes_received > 0) {
    const size_t player_states =
        static_cast<size_t>(bytes_received) / sizeof(Packet);
    for (size_t i = 0; i < player_states; ++i) {
      auto& packet = packets.at(i);

      // If we haven't been assigned an ID yet, the very first non‑zero packet
      // we see is the one the server sent us with our new client ID, stored in
      // `client_id_` for future reference.
      if (client_id_ == 0 && packet.id != 0) {
        client_id_ = packet.id;
        Logger::Debug("Game", "Received client ID from server: " +
                                  std::to_string(client_id_));
      }

      // Skip information about ourselves.
      if (client_id_ == packet.id) {
        Logger::Debug("Game", "Skipping packet with our own client ID: " +
                                  std::to_string(packet.id));
        continue;
      }

      auto it = others_players_.find(packet.id);
      if (it == others_players_.end()) {
        auto new_player = std::make_unique<Player>();
        new_player->SetCoordinate(packet.x_pos, packet.y_pos);
        others_players_[packet.id] = std::move(new_player);
        Logger::Debug("Game",
                      "Added new player with ID: " + std::to_string(packet.id));
      } else {
        it->second->SetCoordinate(packet.x_pos, packet.y_pos);
        Logger::Debug("Game",
                      "Updated player with ID: " + std::to_string(packet.id));
      }
    }
  }

  // Send our current state. If `client_id_` is still zero the server will treat
  // it as a registration packet and reply with an ID).
  const auto& [x_pos, y_pos] = player_->GetCoordinate();
  Packet out{.id = client_id_, .x_pos = x_pos, .y_pos = y_pos};
  client_->Send(&out, sizeof(out));
  Logger::Debug("Game", "Sent our state to server from client ID: " +
                            std::to_string(client_id_));
}
