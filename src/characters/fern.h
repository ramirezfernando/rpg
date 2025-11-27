#pragma once

#include <SDL2/SDL.h>

#include "character.h"

class Fern : public Character {
 public:
  Fern();
  ~Fern() = default;
  int GetSpriteIndex(Direction direction) const override;
};