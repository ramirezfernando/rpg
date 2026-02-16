#include "game.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <memory>

#include "constants/game_constants.h"
#include "core/window.h"
#include "entities/actions/npc_movement_handler.h"
#include "entities/actions/player_input_handler.h"
#include "entities/entity.h"
#include "entities/npc.h"
#include "entities/player.h"
#include "graphics/renderer.h"
#include "graphics/sprite.h"
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

  npc_ = std::make_unique<Npc>();
  Logger::Debug("Game", "NPC character created");

  map_ = std::make_unique<Map>();
  Logger::Debug("Game", "Map created");

  hud_ = std::make_unique<HUD>();
  Logger::Debug("Game", "HUD created");
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
  map_->RenderMailbox();
  map_->RenderPlants();
  map_->RenderClothingRack();

  const bool player_behind =
      player_->IsBehindFence() || IsBehindHouse(player_->GetCoordinate());
  const bool npc_behind =
      npc_->IsBehindFence() || IsBehindHouse(npc_->GetCoordinate());

  // Render characters that should appear behind fence/house
  if (player_behind) {
    player_->Render();
  }
  if (npc_behind) {
    npc_->Render();
  }

  map_->RenderWoodFence();
  map_->RenderHouse();

  // Render characters that should appear in front of fence/house
  if (!player_behind) {
    player_->Render();
  }
  if (!npc_behind) {
    npc_->Render();
  }

  hud_->RenderHotBar();

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
  NpcMovementHandler::UpdateNpcMovement(*npc_);
}
