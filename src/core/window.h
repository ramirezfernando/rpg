#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Window {
 public:
  Window(const char* title, int x, int y, int width, int height);
  ~Window();
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;

  [[nodiscard]] SDL_Window* GetSDLWindow() const { return window_; }

 private:
  SDL_Window* window_{nullptr};
};