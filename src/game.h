#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#include <memory>

#include "characters/character.h"
#include "map/map.h"

class Game {
 public:
  ~Game();
  void Init(const char* title, int x_pos, int y_pos, int width, int height);
  void Render();
  void HandleEvents();
  void SetIsRunning(bool is_running) { is_running_ = is_running; }
  bool IsRunning() { return is_running_; }
  static SDL_Renderer* renderer_;
  static SDL_Event event_;

  SDL_Window* window_;
  bool is_running_;
  std::unique_ptr<Character> player_;
  std::unique_ptr<Map> map_;
};
