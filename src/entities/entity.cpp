#include "entity.h"

#include <iostream>
#include <sstream>

#include "util/logger.h"

Entity::Entity(Sprite* renderer)
    : renderer_(renderer),
      direction_(Direction::Down),
      action_(Action::Idle),
      animation_frame_index_(0),
      // Counters to control animation speed.
      idle_animation_counter_(0),
      walk_animation_counter_(0),
      run_animation_counter_(0),
      // Initial position in front of the house.
      dst_x_(Constants::PLAYER_START_X),
      dst_y_(Constants::PLAYER_START_Y),
      is_npc_(false) {}

void Entity::Render() {
  if (!renderer()) {
    return;
  }

  int initial_index = GetInitialAnimationFrame(action_, direction_);
  int columns = GetSpriteSheetColumns();

  // Use columns (frames per row) to wrap the animation frame.
  int frame = animation_frame_index_ % columns;

  // Compute final index and guard against exceeding sprite_count_.
  int final_index = initial_index + frame;
  int sprite_count = renderer()->GetSpriteCount();
  if (final_index >= sprite_count) {
    std::ostringstream oss;
    oss << "Entity::Render: final_index " << final_index << " >= sprite_count "
        << sprite_count << ", wrapping";
    Logger::Warning("Entity", oss.str());
    final_index %= sprite_count;
  }

  renderer()->RenderSprite(final_index, /*dst_x=*/dst_x_,
                           /*dst_y=*/dst_y_,
                           /*invert=*/direction_ == Direction::Left);
}

void Entity::IncrementAnimationFrameIndexAfterInterval() {
  switch (action_) {
    case Action::Idle:
      if (idle_animation_counter_ >=
          Constants::CHARACTER_IDLE_ANIMATION_SPEED) {
        animation_frame_index_ += 1;
        idle_animation_counter_ = 0;
      }
      idle_animation_counter_++;
      break;
    case Action::Walk:
      if (walk_animation_counter_ >=
          Constants::CHARACTER_WALK_AND_RUN_ANIMATION_SPEED) {
        animation_frame_index_ += 1;
        walk_animation_counter_ = 0;
      }
      walk_animation_counter_++;
      break;
    case Action::Run:
      if (run_animation_counter_ >=
          Constants::CHARACTER_WALK_AND_RUN_ANIMATION_SPEED) {
        animation_frame_index_ += 1;
        run_animation_counter_ = 0;
      }
      run_animation_counter_++;
      break;
  }
}