#pragma once

#include <SDL2/SDL.h>

#include "character.h"

class Fern : public Character {
 public:
  Fern();
  ~Fern() = default;
  int GetInitialAnimationFrame(Direction direction) const override;
  int GetSpriteSheetColumns() const override;
  void SetPathForAction(Action action) override;

 private:
  int sprite_sheet_columns_;
};