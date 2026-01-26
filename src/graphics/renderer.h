#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer {
 public:
  Renderer(SDL_Window* window);
  ~Renderer();
  static SDL_Renderer* renderer_;
};