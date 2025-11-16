#include "game.h"
#include "characters/character.h"
#include "characters/character_elf.h"
#include "constants/constants.h"
#include "map/sprite_sheet_manager.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

Game::~Game() {
  // Cleans up SDL
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  player_.reset();
  tile_map_.reset();
  tiny_house_.reset();
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

  tile_map_ = std::unique_ptr<SpriteSheetManager>(new SpriteSheetManager(
      Constants::TILE_SET_PATH, Constants::TILE_WIDTH, Constants::TILE_HEIGHT));
  if (tile_map_ && tile_map_->LoadSpriteSheet()) {
    std::cout << "Tile map created" << std::endl;
  }

  tiny_house_ = std::unique_ptr<SpriteSheetManager>(new SpriteSheetManager(
      "assets/map/tiny_house.png", Constants::TINY_HOUSE_WIDTH,
      Constants::TINY_HOUSE_HEIGHT));
  if (tiny_house_ && tiny_house_->LoadSpriteSheet()) {
    std::cout << "Tiny house created" << std::endl;
  }
}

void Game::Update() {
  player_->Update();
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  if (tile_map_) {
    tile_map_->RenderSpriteSheet(Constants::FULL_MAP, Constants::TILE_WIDTH,
                                 Constants::TILE_HEIGHT, 0, 0,
                                 Constants::SPRITE_SCALE);
  }
  if (tiny_house_) {
    tiny_house_->RenderSpriteSheet(nullptr, /* map_columns= */ 1,
                                   /* map_rows= */ 1,
                                   /* dst_x= */ Constants::TINY_HOUSE_X_POS,
                                   /* dst_y= */ Constants::TINY_HOUSE_Y_POS,
                                   /* scale= */ Constants::SPRITE_SCALE);
  }
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