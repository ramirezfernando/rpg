#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "sprite/sprite_sheet_renderer.h"

class Character {
 public:
  explicit Character(std::unique_ptr<SpriteSheetRenderer> renderer);
  virtual ~Character() = default;
  void Update();
  void Render();

 protected:
  // Pure-virtual hook for derived classes to customize what is rendered.
  virtual int GetSpriteIndex() const = 0;

  SpriteSheetRenderer* renderer() { return renderer_.get(); }

 private:
  std::unique_ptr<SpriteSheetRenderer> renderer_;
};