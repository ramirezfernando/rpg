#pragma once

#include <SDL2/SDL.h>

#include "constants/entity_constants.h"
#include "graphics/sprite.h"

enum class Direction : std::uint8_t { Up, Down, Left, Right };
enum class Action : std::uint8_t { Idle, Walk, Run };

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
  void SetSprite(Sprite* sprite) { sprite_ = sprite; }

 private:
  Sprite* sprite_;
  Direction direction_{Direction::Down};
  Action action_{Action::Idle};
  int animation_frame_index_{0};
  int idle_animation_counter_{0};
  int walk_animation_counter_{0};
  int run_animation_counter_{0};
  int dst_x_{Constants::PLAYER_START_X};
  int dst_y_{Constants::PLAYER_START_Y};
  bool is_npc_{false};
};