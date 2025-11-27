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
  void Render();
  void IncrementAnimationFrameIndex() { animation_frame_index_ += 1; }
  // Getters
  int GetXPos() { return dst_x_; }
  int GetYPos() { return dst_y_; }
  // Setters
  void SetXPos(int dst_x) { dst_x_ = dst_x; }
  void SetYPos(int dst_y) { dst_y_ = dst_y; }
  void SetDirectionFacing(Direction direction) { direction_ = direction; }
  virtual void SetPathForAction(Action action) = 0;

 protected:
  // Pure-virtual hooks for derived classes to customize what is rendered.
  virtual int GetInitialAnimationFrame(Direction direction) const = 0;
  virtual int GetSpriteSheetColumns() const = 0;

  SpriteSheetRenderer* renderer() { return renderer_.get(); }

 private:
  std::unique_ptr<SpriteSheetRenderer> renderer_;
  Direction direction_;
  int animation_frame_index_;
  int dst_x_;
  int dst_y_;
};