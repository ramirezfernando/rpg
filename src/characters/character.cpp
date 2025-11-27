#include "character.h"

#include <iostream>

Character::Character(std::unique_ptr<SpriteSheetRenderer> renderer)
    : renderer_(std::move(renderer)) {}

void Character::Update() {}

void Character::Render() {
  if (!renderer())
    return;
  renderer()->RenderSprite(1, /*dst_x=*/0, /*dst_y=*/0);
}