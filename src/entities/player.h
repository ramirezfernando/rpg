#pragma once

#include <SDL2/SDL.h>

#include "entity.h"

class Player : public Entity {
 public:
  Player();
  ~Player() override = default;
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

  // Getters
  [[nodiscard]] int GetInitialAnimationFrame(
      Action action, Direction direction) const override;
  [[nodiscard]] int GetSpriteSheetColumns() const override;

  // Setters
  void SetPathForAction(Action action) override;

 private:
  int sprite_sheet_columns_;
};