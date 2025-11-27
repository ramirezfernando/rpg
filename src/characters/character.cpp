#include "character.h"

#include <iostream>

Character::Character(std::unique_ptr<SpriteSheetRenderer> renderer)
    : renderer_(std::move(renderer)),
      direction_(Direction::Down),
      animation_frame_index_(0) {}

void Character::Update() {}

void Character::Render() {
  if (!renderer()) {
    return;
  }

  int base_index = GetSpriteIndex(direction_);
  int columns = GetSpriteSheetColumns();

  int frame = animation_frame_index_ % columns;
  // Render using current animation frame (wrap safely).
  renderer()->RenderSprite(base_index + frame, /*dst_x=*/0, /*dst_y=*/0,
                           /*scale=*/3,
                           /*invert=*/direction_ == Direction::Left);
}