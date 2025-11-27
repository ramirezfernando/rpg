#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "sprite/sprite_sheet_renderer.h"

enum class Direction { Up, Down, Left, Right };
enum class Action { Walk };

class Character {
 public:
  explicit Character(std::unique_ptr<SpriteSheetRenderer> renderer);
  virtual ~Character() = default;
  void Update();
  void Render();
  virtual void SetPathForAction(Action action) = 0;
  void SetDirectionFacing(Direction direction) { direction_ = direction; }
  void IncrementAnimationFrameIndex() { animation_frame_index_ += 1; }

 protected:
  // Pure-virtual hooks for derived classes to customize what is rendered.
  virtual int GetInitialAnimationFrame(Direction direction) const = 0;
  virtual int GetSpriteSheetColumns() const = 0;

  SpriteSheetRenderer* renderer() { return renderer_.get(); }

 private:
  std::unique_ptr<SpriteSheetRenderer> renderer_;
  Direction direction_;
  int animation_frame_index_;
};