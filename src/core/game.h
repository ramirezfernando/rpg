#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#include <memory>

#include "entities/entity.h"
#include "graphics/renderer.h"
#include "resource/resource_manager.h"
#include "ui/hud.h"
#include "window.h"
#include "world/map.h"

class Game {
 public:
  ~Game();
  void Init();
  void Render();
  void Update();
  void SetIsRunning(bool is_running) { is_running_ = is_running; }
  bool IsRunning() { return is_running_; }
  static SDL_Event event_;

  bool is_running_;
  std::unique_ptr<Window> window_;
  std::unique_ptr<Renderer> renderer_;
  std::unique_ptr<Entity> player_;
  std::unique_ptr<Entity> npc_;
  std::unique_ptr<Map> map_;
  std::unique_ptr<HUD> hud_;
};
