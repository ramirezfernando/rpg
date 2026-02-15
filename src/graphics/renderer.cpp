#include "renderer.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "util/logger.h"

SDL_Renderer* Renderer::renderer_ = nullptr;

Renderer::Renderer(SDL_Window* window) {
  renderer_ = SDL_CreateRenderer(window, nullptr);
  if (renderer_ != nullptr) {
    // Set default draw color to white.
    const int color_value = 255;
    SDL_SetRenderDrawColor(renderer_, color_value, color_value, color_value,
                           color_value);
    Logger::Debug("Renderer", "Renderer created");
  } else {
    Logger::Error("Renderer", "Failed to create renderer");
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer_);
  Logger::Debug("Renderer", "Renderer destroyed");
}