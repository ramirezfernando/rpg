#include "window.h"

#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_video.h>

#include "util/logger.h"

Window::Window(const char* title, int x, int y, int width, int height) {
  const SDL_PropertiesID props = SDL_CreateProperties();
  SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, x);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, y);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
  window_ = SDL_CreateWindowWithProperties(props);
  SDL_DestroyProperties(props);
  if (window_ != nullptr) {
    Logger::Debug("Game", "Window created");
  } else {
    Logger::Error("Game", "Failed to create window");
  }
}

Window::~Window() {
  SDL_DestroyWindow(window_);
  Logger::Debug("Window", "Window destroyed");
}
