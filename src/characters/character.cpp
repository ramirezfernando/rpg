#include "character.h"

#include <iostream>

Character::Character(std::unique_ptr<SpriteSheetRenderer> renderer)
    : renderer_(std::move(renderer)), direction_(Direction::Down) {}

void Character::Update() {}

void Character::Render() {
  if (!renderer()) {
    return;
  }
  renderer()->RenderSprite(GetSpriteIndex(direction_), /*dst_x=*/0,
                           /*dst_y=*/0, /*scale=*/3,
                           /*invert=*/direction_ == Direction::Left);
}