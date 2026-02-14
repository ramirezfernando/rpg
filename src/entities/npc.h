#pragma once

#include <SDL3/SDL.h>

#include "entity.h"

class Npc : public Entity {
 public:
  Npc();
  ~Npc() override = default;
  Npc(const Npc&) = delete;
  Npc& operator=(const Npc&) = delete;
  Npc(Npc&&) = delete;
  Npc& operator=(Npc&&) = delete;

  // Getters
  [[nodiscard]] int GetInitialAnimationFrame(
      Action action, Direction direction) const override;
  [[nodiscard]] int GetSpriteSheetColumns() const override;

  // Setters
  void SetPathForAction(Action action) override;

 private:
  int sprite_sheet_columns_;
};