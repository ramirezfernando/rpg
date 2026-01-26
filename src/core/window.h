#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window {
 public:
  Window(const char* title, int x, int y, int width, int height);
  ~Window();
  SDL_Window* GetSDLWindow() const { return window_; }

 private:
  SDL_Window* window_;
};