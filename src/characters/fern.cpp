#include "fern.h"

#include <iostream>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"
Fern::Fern()
    : Character(std::make_unique<SpriteSheetRenderer>(
          /*path=*/"assets/sprites/characters/fern/walk.png",
          /*sprite_w=*/32, /*sprite_h=*/32)) {
  renderer()->LoadSpriteSheet();
  sprite_sheet_columns_ = renderer()->GetColumns();
  std::cout << sprite_sheet_columns_;
}

int Fern::GetSpriteIndex(Direction direction) const {
  switch (direction) {
    case Direction::Up:
      return 6;
    case Direction::Down:
      return 0;
    // Left and Right indicies on the fern sprite sheet are the same, they just
    // need to be inverted when rendered.
    case Direction::Left:
    case Direction::Right:
      return 12;
  }
}

int Fern::GetSpriteSheetColumns() const {
  return sprite_sheet_columns_;
}