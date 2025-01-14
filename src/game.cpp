#include "game.h"
#include<unistd.h>

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

void Game::Init(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen) {
  int flags = 0;
  if (full_screen == true) {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  // Initializing SDL2 window
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags); 
    if (window_) {
      cout << "Window created" << endl;
    }
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_) {
      SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
      cout << "Renderer created" << endl;
    }
    is_running_ = true;
  } 
  else {
    is_running_ = false;
  }
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
  return;
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  SDL_RenderPresent(renderer_); // Double buffering
}

void Game::Clean() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
  IMG_Quit();
  cout << "Game cleaned" << endl;
}

void Game::SetIsRunning(bool is_running) {
  is_running_ = is_running;
}

bool Game::GetIsRunning() {
  return is_running_;
}