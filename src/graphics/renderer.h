#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Renderer {
 public:
  explicit Renderer(SDL_Window* window);
  ~Renderer();
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  Renderer(Renderer&&) = delete;
  Renderer& operator=(Renderer&&) = delete;

  static SDL_Renderer* renderer_;
};