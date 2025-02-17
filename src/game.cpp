#include "game.h"
#include "background.h"
#include "characters/character.h"
#include "characters/character_elf.h"
#include "characters/character_mage.h"
#include "constants/asset_constants.h"
#include "constants/game_constants.h"
#include "enemies/enemy.h"
#include "enemies/enemy_ghost.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;
std::unique_ptr<Background> background;
std::unique_ptr<Character> player;
std::unique_ptr<Enemy> enemy;

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

  // Setup background
  background = std::unique_ptr<Background>(
      new Background(Constants::BACKGROUND_FILE_PATH));
  if (background) {
    std::cout << "Background created" << std::endl;
  }

  // Setup player
  player = std::unique_ptr<Character>(
      new Elf(Constants::WINDOW_SIZE / 2, Constants::WINDOW_SIZE / 2));
  if (player) {
    std::cout << "Character created" << std::endl;
  }

  // Setup enemy
  enemy = std::unique_ptr<Enemy>(new Ghost(0, 0));
  if (enemy) {
    std::cout << "Enemy created" << std::endl;
  }
}

void Game::Update() {
  background->Update();
  player->Update();
  enemy->Update(player->GetXPos(), player->GetYPos());
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  background->Render();
  player->Render();
  enemy->Render();
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
          break;
        case SDLK_DOWN:
          player->SetYPos(player->GetYPos() +
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::DOWN);
          break;
        case SDLK_LEFT:
          player->SetXPos(player->GetXPos() -
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::LEFT);
          break;
        case SDLK_RIGHT:
          player->SetXPos(player->GetXPos() +
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPathFromDirection(Constants::Direction::RIGHT);
          break;
        case SDLK_a:
          player->SetShouldAttack(true);
          break;
        default:
          break;
      }
      break;
  }
}