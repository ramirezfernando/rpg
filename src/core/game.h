#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#include <memory>

#include "cache/cache.h"
#include "entities/entity.h"
#include "graphics/renderer.h"
#include "ui/hud.h"
#include "window.h"
#include "world/map.h"

class Game {
 public:
  Game();
  ~Game();
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  void Render();
  void Update();
  void SetIsRunning(bool is_running) { is_running_ = is_running; }
  [[nodiscard]] bool IsRunning() const { return is_running_; }
  static SDL_Event event_;

 private:
  bool is_running_{false};
  std::unique_ptr<Window> window_;
  std::unique_ptr<Renderer> renderer_;
  std::unique_ptr<Entity> player_;
  std::unique_ptr<Entity> npc_;
  std::unique_ptr<Map> map_;
  std::unique_ptr<HUD> hud_;
};
