#include "entity.h"

#include <iostream>
#include <sstream>

#include "constants/entity_constants.h"
#include "graphics/sprite.h"
#include "util/logger.h"

Entity::Entity(const Sprite* sprite) : sprite_(sprite) {}

void Entity::Render() {
  if (sprite() == nullptr) {
    return;
  }

  const int initial_index = GetInitialAnimationFrame(action_, direction_);
  const int columns = GetSpriteSheetColumns();

  // Use columns (frames per row) to wrap the animation frame.
  const int frame = animation_frame_index_ % columns;

  // Compute final index and guard against exceeding sprite_count_.
  int final_index = initial_index + frame;
  const int sprite_count = sprite()->GetSpriteCount();
  if (final_index >= sprite_count) {
    std::ostringstream oss;
    oss << "Entity::Render: final_index " << final_index << " >= sprite_count "
        << sprite_count << ", wrapping";
    Logger::Warning("Entity", oss.str());
    final_index %= sprite_count;
  }

  sprite()->RenderSprite(final_index, /*dst_x=*/dst_x_,
                         /*dst_y=*/dst_y_,
                         /*invert=*/direction_ == Direction::Left);
}

void Entity::IncrementAnimationFrameIndexAfterInterval() {
  switch (action_) {
    case Action::Idle:
      if (idle_animation_counter_ >= Constants::ENTITY_IDLE_ANIMATION_SPEED) {
        animation_frame_index_ += 1;
        idle_animation_counter_ = 0;
      }
      idle_animation_counter_++;
      break;
    case Action::Walk:
      if (walk_animation_counter_ >=
          Constants::ENTITY_WALK_AND_RUN_ANIMATION_SPEED) {
        animation_frame_index_ += 1;
        walk_animation_counter_ = 0;
      }
      walk_animation_counter_++;
      break;
    case Action::Run:
      if (run_animation_counter_ >=
          Constants::ENTITY_WALK_AND_RUN_ANIMATION_SPEED) {
        animation_frame_index_ += 1;
        run_animation_counter_ = 0;
      }
      run_animation_counter_++;
      break;
  }
}