#pragma once

#include <SDL3/SDL.h>

#include <cstdint>

#include "constants/entity_constants.h"
#include "graphics/sprite.h"

enum class Direction : std::uint8_t { Up, Down, Left, Right };
enum class Action : std::uint8_t { Idle, Walk, Run };

class Entity {
 public:
  explicit Entity(const Sprite* sprite);
  virtual ~Entity() = default;
  Entity(const Entity&) = delete;
  Entity& operator=(const Entity&) = delete;
  Entity(Entity&&) = delete;
  Entity& operator=(Entity&&) = delete;

  void Render();
  void IncrementAnimationFrameIndexAfterInterval();

  // Getters:
  [[nodiscard]] Sprite::Coordinate GetCoordinate() const { return coordinate_; }
  [[nodiscard]] Action GetCurrentAction() const { return action_; }
  [[nodiscard]] bool IsNpc() const { return is_npc_; }

  // Setters:
  void SetAction(Action action) { action_ = action; }
  void SetCoordinate(Sprite::Coordinate coordinate) {
    coordinate_ = coordinate;
  }
  void SetDirectionFacing(Direction direction) { direction_ = direction; }
  void SetIsNpc(bool is_npc) { is_npc_ = is_npc; }
  virtual void SetPathForAction(Action action) = 0;

 protected:
  // Pure-virtual hooks for derived classes to customize what is rendered.
  [[nodiscard]] virtual int GetInitialAnimationFrame(
      Action action, Direction direction) const = 0;
  [[nodiscard]] virtual int GetSpriteSheetColumns() const = 0;

  const Sprite* sprite() { return sprite_; }
  void SetSprite(const Sprite* sprite) { sprite_ = sprite; }

 private:
  // Non-owning pointer to cached sprite.
  const Sprite* sprite_;

  Direction direction_{Direction::Down};
  Action action_{Action::Idle};
  int animation_frame_index_{0};
  int idle_animation_counter_{0};
  int walk_animation_counter_{0};
  int run_animation_counter_{0};
  Sprite::Coordinate coordinate_{.x_pos = Constants::PLAYER_START_X,
                                 .y_pos = Constants::PLAYER_START_Y};
  bool is_npc_{false};
};