#include "renderer.h"

#include "util/logger.h"

SDL_Renderer* Renderer::renderer_ = nullptr;

Renderer::Renderer(SDL_Window* window) {
  renderer_ = SDL_CreateRenderer(window, -1, 0);
  if (renderer_) {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    Logger::Debug("Renderer", "Renderer created");
  } else {
    Logger::Error("Renderer", "Failed to create renderer");
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer_);
  Logger::Debug("Renderer", "Renderer destroyed");
}