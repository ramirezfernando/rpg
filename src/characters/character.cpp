#include "character.h"

#include <iostream>

Character::Character(SpriteSheetRenderer* renderer)
    : renderer_(renderer),
      direction_(Direction::Down),
      action_(Action::Idle),
      animation_frame_index_(0),
      // Initial position in front of the house.
      dst_x_(Constants::PLAYER_START_X),
      dst_y_(Constants::PLAYER_START_Y) {}

void Character::Render() {
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
#if defined(DEBUG_MODE)
    std::cerr << "Character::Render: final_index " << final_index
              << " >= sprite_count " << sprite_count << ", wrapping\n";
#endif
    final_index %= sprite_count;
  }

  renderer()->RenderSprite(final_index, /*dst_x=*/dst_x_,
                           /*dst_y=*/dst_y_,
                           /*invert=*/direction_ == Direction::Left);
}