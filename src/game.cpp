#include "game.h"

#include <iostream>

#include "characters/character.h"
#include "characters/fern.h"
#include "constants/constants.h"
#include "map/map_renderer.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

Game::~Game() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
  IMG_Quit();
#if defined(DEBUG_MODE)
  std::cout << "Game destroyed" << std::endl;
#endif  // DEBUG_MODE
}

void Game::Init(const char* title, int x_pos, int y_pos, int width,
                int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, 0);
    if (window_) {
#if defined(DEBUG_MODE)
      std::cout << "Window created" << std::endl;
#endif  // DEBUG_MODE
    }
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_) {
      SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
#if defined(DEBUG_MODE)
      std::cout << "Renderer created" << std::endl;
#endif  // DEBUG_MODE
    }
    is_running_ = true;
  } else {
    is_running_ = false;
  }

  player_ = std::unique_ptr<Character>(new Fern());
  if (player_) {
#if defined(DEBUG_MODE)
    std::cout << "Character created" << std::endl;
#endif  // DEBUG_MODE
  }
  map_renderer_ = std::unique_ptr<MapRenderer>(new MapRenderer());
  if (map_renderer_) {
#if defined(DEBUG_MODE)
    std::cout << "Map renderer created" << std::endl;
#endif  // DEBUG_MODE
  }
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  // Order of rendering matters: first rendered = back, last rendered = front.
  map_renderer_->RenderGrassTiles();
  map_renderer_->RenderGrassWater();
  map_renderer_->RenderWoodFence();
  map_renderer_->RenderTinyHouse();
  map_renderer_->RenderWaterfall();
  map_renderer_->RenderCliff();
  player_->Render();
  SDL_RenderPresent(renderer_);  // Double buffering
}

void Game::HandleEvents() {
  SDL_PollEvent(&event_);
  switch (event_.type) {
    case SDL_QUIT:
      is_running_ = false;
      break;
    case SDL_KEYDOWN:
      switch (event_.key.keysym.sym) {
        case SDLK_w:
          player_->SetYPos(player_->GetYPos() -
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetPathForAction(Action::Walk);
          player_->SetDirectionFacing(Direction::Up);
          player_->IncrementAnimationFrameIndex();
          break;
        case SDLK_s:
          player_->SetYPos(player_->GetYPos() +
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetPathForAction(Action::Walk);
          player_->SetDirectionFacing(Direction::Down);
          player_->IncrementAnimationFrameIndex();
          break;
        case SDLK_a:
          player_->SetXPos(player_->GetXPos() -
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetPathForAction(Action::Walk);
          player_->SetDirectionFacing(Direction::Left);
          player_->IncrementAnimationFrameIndex();
          break;
        case SDLK_d:
          player_->SetXPos(player_->GetXPos() +
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetPathForAction(Action::Walk);
          player_->SetDirectionFacing(Direction::Right);
          player_->IncrementAnimationFrameIndex();
          break;
        default:
          break;
      }
      break;
  }
}