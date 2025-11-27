#include "fern.h"

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

Fern::Fern()
    : Character(std::make_unique<SpriteSheetRenderer>(
          /*path=*/"assets/sprites/characters/fern/walk.png",
          /*sprite_w=*/32, /*sprite_h=*/32)) {}