#include "window.h"

#include "util/logger.h"

Window::Window(const char* title, int x, int y, int width, int height)
    : window_(SDL_CreateWindow(title, x, y, width, height, /*flags=*/0)) {
  if (window_) {
    Logger::Debug("Game", "Window created");
  } else {
    Logger::Error("Game", "Failed to create window");
  }
}

Window::~Window() {
  SDL_DestroyWindow(window_);
  Logger::Debug("Window", "Window destroyed");
}
