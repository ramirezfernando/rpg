#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <memory>

#include "constants/game_constants.h"
#include "core/window.h"
#include "entities/actions/npc_movement_handler.h"
#include "entities/actions/player_input_handler.h"
#include "entities/entity.h"
#include "entities/npc.h"
#include "entities/player.h"
#include "graphics/renderer.h"
#include "ui/hud.h"
#include "util/logger.h"
#include "world/map.h"

namespace {

bool IsPlayerBehindFence(int x, int y) {
  // Left-most fence where player can be behind.
  const int left_fence_y_top_position = 260;
  const int left_fence_y_bottom_position = 300;
  const int left_fence_x_right_position = 260;

  // Right-most fence where player can be behind.
  const int right_fence_y_top_position = 400;
  const int right_fence_y_bottom_position = 440;

  return (y >= right_fence_y_top_position &&
          y <= right_fence_y_bottom_position) ||
         (y >= left_fence_y_top_position && y <= left_fence_y_bottom_position &&
          x <= left_fence_x_right_position);
}

bool IsPlayerBehindHouse(int x, int y) {
  const int house_x_position = 670;
  const int house_y_position = 200;
  return y <= house_y_position && x <= house_x_position;
}

bool ShouldRenderPlayerFirst(int x, int y) {
  return IsPlayerBehindFence(x, y) || IsPlayerBehindHouse(x, y);
}

}  // anonymous namespace

SDL_Event Game::event_;

Game::Game() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
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
  IMG_Quit();
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

  bool player_behind =
      ShouldRenderPlayerFirst(player_->GetXPos(), player_->GetYPos());
  bool npc_behind = ShouldRenderPlayerFirst(npc_->GetXPos(), npc_->GetYPos());

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

  map_->RenderClothingRack();

  hud_->RenderHotBar();

  SDL_RenderPresent(Renderer::renderer_);  // Double buffering
}

void Game::Update() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      is_running_ = false;
    }
  }
  InputHandler::HandleInput(*player_, *map_, *hud_);
  NpcMovementHandler::UpdateNpcMovement(*npc_, *map_);
}
