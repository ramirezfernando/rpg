#include "game.h"
#include "characters/character.h"
#include "characters/character_elf.h"
#include "constants/constants.h"
#include "map/map_renderer.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

Game::~Game() {
  // Cleans up SDL
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
  IMG_Quit();
  std::cout << "Game destroyed" << std::endl;
}

void Game::Init(const char* title, int x_pos, int y_pos, int width,
                int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, 0);
    if (window_) {
      std::cout << "Window created" << std::endl;
    }
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_) {
      SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
      std::cout << "Renderer created" << std::endl;
    }
    is_running_ = true;
  } else {
    is_running_ = false;
  }

  player_ = std::unique_ptr<Character>(
      new Elf(Constants::WINDOW_SIZE / 2, Constants::WINDOW_SIZE / 2));
  if (player_) {
    std::cout << "Character created" << std::endl;
  }
  map_renderer_ = std::unique_ptr<MapRenderer>(new MapRenderer());
  if (map_renderer_) {
    std::cout << "Map renderer created" << std::endl;
  }
}

void Game::Update() {
  player_->Update();
}

void Game::Render() {
  SDL_RenderClear(renderer_);
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
        case SDLK_UP:
          player_->SetYPos(player_->GetYPos() -
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetFolderPathFromDirection(Constants::Direction::UP);
          player_->SetDirectionFacing(Constants::Direction::UP);
          break;
        case SDLK_DOWN:
          player_->SetYPos(player_->GetYPos() +
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetFolderPathFromDirection(Constants::Direction::DOWN);
          player_->SetDirectionFacing(Constants::Direction::DOWN);
          break;
        case SDLK_LEFT:
          player_->SetXPos(player_->GetXPos() -
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetFolderPathFromDirection(Constants::Direction::LEFT);
          player_->SetDirectionFacing(Constants::Direction::LEFT);
          break;
        case SDLK_RIGHT:
          player_->SetXPos(player_->GetXPos() +
                           Constants::CHARACTER_MOVEMENT_GAP);
          player_->SetFolderPathFromDirection(Constants::Direction::RIGHT);
          player_->SetDirectionFacing(Constants::Direction::RIGHT);
          break;
        default:
          break;
      }
      break;
  }
}