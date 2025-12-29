#pragma once

#include <SDL2/SDL.h>

#include "character.h"

class Kat : public Character {
 public:
  Kat();
  ~Kat() = default;

  // Getters
  int GetInitialAnimationFrame(Action action,
                               Direction direction) const override;
  int GetSpriteSheetColumns() const override;

  // Setters
  void SetPathForAction(Action action) override;

 private:
  int sprite_sheet_columns_;
};