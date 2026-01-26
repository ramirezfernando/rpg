#include "game.h"

#include <iostream>

#include "entity/actions/npc_movement_handler.h"
#include "entity/actions/player_input_handler.h"
#include "entity/character.h"
#include "entity/fern.h"
#include "entity/kat.h"
#include "graphics/hud.h"
#include "graphics/map.h"
#include "util/constants.h"
#include "util/logger.h"

SDL_Event Game::event_;

static bool IsPlayerBehindFence(int x, int y) {
  return (y >= 400 && y <= 440) || (y >= 260 && y <= 300 && x <= 260);
}

static bool IsPlayerBehindHouse(int x, int y) {
  return y <= 200 && x <= 670;
}

static bool ShouldRenderPlayerFirst(int x, int y) {
  return IsPlayerBehindFence(x, y) || IsPlayerBehindHouse(x, y);
}

Game::~Game() {
  // Clear resource cache before destroying SDL objects.
  ResourceManager::GetInstance().Clear();

  SDL_Quit();
  IMG_Quit();

  Logger::Debug("Game", "Game destroyed");
}

void Game::Init() {
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

  player_ = std::make_unique<Fern>();
  Logger::Debug("Game", "Player character created");

  npc_ = std::make_unique<Kat>();
  Logger::Debug("Game", "NPC character created");

  map_ = std::make_unique<Map>();
  Logger::Debug("Game", "Map created");

  hud_ = std::make_unique<HUD>();
  Logger::Debug("Game", "HUD created");
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
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      is_running_ = false;
    }
  }
  InputHandler::HandleInput(player_.get(), map_.get(), hud_.get());
  NpcMovementHandler::UpdateNpcMovement(npc_.get(), map_.get());
}
