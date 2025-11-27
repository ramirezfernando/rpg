#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "sprite/sprite_sheet_renderer.h"

enum class Direction { Up, Down, Left, Right };

class Character {
 public:
  explicit Character(std::unique_ptr<SpriteSheetRenderer> renderer);
  virtual ~Character() = default;
  void Update();
  void Render();
  void SetDirectionFacing(Direction direction) { direction_ = direction; }

 protected:
  // Pure-virtual hook for derived classes to customize what is rendered.
  virtual int GetSpriteIndex(Direction direction) const = 0;

  SpriteSheetRenderer* renderer() { return renderer_.get(); }

 private:
  Direction direction_;
  std::unique_ptr<SpriteSheetRenderer> renderer_;
};