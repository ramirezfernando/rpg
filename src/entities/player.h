#pragma once

#include <SDL2/SDL.h>

#include "entity.h"

class Player : public Entity {
 public:
  Player();
  ~Player() = default;

  // Getters
  int GetInitialAnimationFrame(Action action,
                               Direction direction) const override;
  int GetSpriteSheetColumns() const override;

  // Setters
  void SetPathForAction(Action action) override;

 private:
  int sprite_sheet_columns_;
};