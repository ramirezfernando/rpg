#include "game.h"
#include "characters/character.h"
#include "characters/character_elf.h"
#include "constants/constants.h"
#include "map/tile_map.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

Game::~Game() {
  // Cleans up SDL
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  player_.reset();
  tile_map_.reset();
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

  tile_map_ = std::unique_ptr<TileMap>(new TileMap(Constants::MAP_TILE_SET_PATH,
                                                   Constants::MAP_TILE_WIDTH,
                                                   Constants::MAP_TILE_HEIGHT));
  if (tile_map_ && tile_map_->Load()) {
    std::cout << "Tile map created" << std::endl;
  }
}

void Game::Update() {
  player_->Update();
}

static inline int TileIndex(int col, int row, int tileset_columns = 4) {
  return row * tileset_columns + col;
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  if (tile_map_) {
    std::vector<int> map = {
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
        TileIndex(0, 4), TileIndex(1, 4), TileIndex(2, 4), TileIndex(3, 4),
        TileIndex(0, 0), TileIndex(1, 0), TileIndex(2, 0), TileIndex(3, 0),
        TileIndex(0, 1), TileIndex(1, 1), TileIndex(2, 1), TileIndex(3, 1),
        TileIndex(0, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(3, 2),
        TileIndex(0, 3), TileIndex(1, 3), TileIndex(2, 3), TileIndex(3, 3),
    };
    tile_map_->RenderTileMap(/*tile_map*/ map, /*tile_map_columns*/ 16,
                             /*tile_map_rows*/ 16,
                             /*dst_x*/ 0,
                             /*dst_y*/ 0,
                             /*scale*/ Constants::SPRITE_SCALE);
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