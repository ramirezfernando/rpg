#include "game.h"
#include "characters/character.h"
#include "characters/character_elf.h"
#include "constants/asset_constants.h"
#include "constants/game_constants.h"
#include "tileset/tileset.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;
std::unique_ptr<Tileset> tileset;
std::unique_ptr<Character> player;

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
  // Initializing SDL2 window
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

  // Setup player
  player = std::unique_ptr<Character>(
      new Elf(Constants::WINDOW_SIZE / 2, Constants::WINDOW_SIZE / 2));
  if (player) {
    std::cout << "Character created" << std::endl;
  }

  tileset =
      std::unique_ptr<Tileset>(new Tileset("assets/tiles/tileset.png", 16, 16));
  if (tileset && tileset->Load()) {
    std::cout << "Tileset loaded\n";
  }
}

void Game::Update() {
  player->Update();
}

static inline int TileIndex(int col, int row, int tileset_columns = 4) {
  return row * tileset_columns + col;
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  // example map (row-major indices). Negative = empty.
  if (tileset) {
    std::vector<int> map = {
        TileIndex(1, 2), TileIndex(1, 2), TileIndex(2, 2), -1,
        TileIndex(1, 2), TileIndex(1, 2), TileIndex(2, 2), -1,
        TileIndex(1, 2), TileIndex(1, 2), TileIndex(2, 2), TileIndex(2, 2),
        TileIndex(1, 2), TileIndex(1, 2), TileIndex(2, 2), -1,
    };
    tileset->RenderMap(map, 4, 4, 0, 0, 2);
  }
  player->Render();
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
          player->SetYPos(player->GetYPos() -
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::UP);
          player->SetDirectionFacing(Constants::Direction::UP);
          break;
        case SDLK_DOWN:
          player->SetYPos(player->GetYPos() +
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::DOWN);
          player->SetDirectionFacing(Constants::Direction::DOWN);
          break;
        case SDLK_LEFT:
          player->SetXPos(player->GetXPos() -
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::LEFT);
          player->SetDirectionFacing(Constants::Direction::LEFT);
          break;
        case SDLK_RIGHT:
          player->SetXPos(player->GetXPos() +
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::RIGHT);
          player->SetDirectionFacing(Constants::Direction::RIGHT);
          break;
        default:
          break;
      }
      break;
  }
}