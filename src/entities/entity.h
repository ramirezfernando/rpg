#pragma once

#include <SDL2/SDL.h>

#include "graphics/sprite.h"

enum class Direction { Up, Down, Left, Right };
enum class Action { Idle, Walk, Run };

class Entity {
 public:
  explicit Entity(Sprite* sprite);
  virtual ~Entity() = default;
  void Render();
  void IncrementAnimationFrameIndexAfterInterval();

  // Getters
  int GetXPos() { return dst_x_; }
  int GetYPos() { return dst_y_; }
  Action GetCurrentAction() const { return action_; }
  bool IsNpc() const { return is_npc_; }

  // Setters
  void SetAction(Action action) { action_ = action; }
  void SetXPos(int dst_x) { dst_x_ = dst_x; }
  void SetYPos(int dst_y) { dst_y_ = dst_y; }
  void SetDirectionFacing(Direction direction) { direction_ = direction; }
  void SetIsNpc(bool is_npc) { is_npc_ = is_npc; }
  virtual void SetPathForAction(Action action) = 0;

 protected:
  // Pure-virtual hooks for derived classes to customize what is rendered.
  virtual int GetInitialAnimationFrame(Action action,
                                       Direction direction) const = 0;
  virtual int GetSpriteSheetColumns() const = 0;

  Sprite* sprite() { return sprite_; }
  void SetRenderer(Sprite* sprite) { sprite_ = sprite; }

 private:
  Sprite* sprite_;
  Direction direction_;
  Action action_;
  int animation_frame_index_;
  int idle_animation_counter_;
  int walk_animation_counter_;
  int run_animation_counter_;
  int dst_x_;
  int dst_y_;
  bool is_npc_;
};