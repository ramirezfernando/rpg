#include "game.h"
#include "background.h"
#include "character.h"
#include "character_mage.h"
#include "constants/asset_constants.h"
#include "constants/game_constants.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;
Background* background;
Character* player;

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
  background = new Background(Constants::BACKGROUND_FILE_PATH, 0, 0);

  // Setup character
  player = new Mage(Constants::CHARACTER_MAGE_DOWN_FOLDER_PATH, 0, 0);
}

void Game::Update() {
  background->Update();
  player->Update();
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  background->Render();
  player->Render();
  SDL_RenderPresent(renderer_);  // Double buffering
}

void Game::Clean() {
  background->Clean();
  player->Clean();
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
  IMG_Quit();
  std::cout << "Game cleaned" << std::endl;
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
          player->SetFolderPath(Constants::CHARACTER_MAGE_UP_FOLDER_PATH);
          break;
        case SDLK_DOWN:
          player->SetYPos(player->GetYPos() +
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPath(Constants::CHARACTER_MAGE_DOWN_FOLDER_PATH);
          break;
        case SDLK_LEFT:
          player->SetXPos(player->GetXPos() -
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPath(Constants::CHARACTER_MAGE_LEFT_FOLDER_PATH);
          break;
        case SDLK_RIGHT:
          player->SetXPos(player->GetXPos() +
                          Constants::CHARACTER_MOVEMENT_GAP);
          player->SetFolderPath(Constants::CHARACTER_MAGE_RIGHT_FOLDER_PATH);
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

void Game::SetIsRunning(bool is_running) {
  is_running_ = is_running;
}

bool Game::GetIsRunning() {
  return is_running_;
}