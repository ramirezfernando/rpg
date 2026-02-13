#pragma once

#include <span>

#include "entities/entity.h"
#include "ui/hud.h"
#include "world/map.h"

// Encapsulates all input handling logic for the player character.
class InputHandler {
 public:
  // Process input for the given character. Returns `true` if the character
  // moved, `false` otherwise.
  static bool HandleInput(Entity& player, HUD& hud);

 private:
  // Getter that turns `SDL_GetKeyboardState` dumb pointer into a smart pointer.
  static std::span<const Uint8> GetKeyboardState();

  // Get keyboard state and compute movement delta.
  static void GetMovementInput(Sprite::Coordinate& coordinate, bool& is_running,
                               Direction& facing_direction);

  // Process HUD input.
  static void GetHudInput(HUD& hud);
};
