#include "game.h"
#include "background.h"
#include "constants.h"
#include <unistd.h>

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;
Background* background;

void Game::Init(const char* title, int x_pos, int y_pos, int width, int height,
                bool full_screen) {
  int flags = 0;
  if (full_screen == true) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  // Initializing SDL2 window
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
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
  background = new Background(Const::BACKGROUND_FILE_PATH, 0, 0);
}

void Game::HandleEvents() {
  SDL_PollEvent(&event_);
  switch (event_.type) {
    case SDL_QUIT:
      is_running_ = false;
      break;
  }
}

void Game::Update() {
  background->Update();
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  background->Render();
  SDL_RenderPresent(renderer_);  // Double buffering
}

void Game::Clean() {
  background->Clean();
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
  IMG_Quit();
  std::cout << "Game cleaned" << std::endl;
}

void Game::SetIsRunning(bool is_running) {
  is_running_ = is_running;
}

bool Game::GetIsRunning() {
  return is_running_;
}