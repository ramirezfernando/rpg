#pragma once

#include "entities/character.h"
#include "graphics/map.h"
#include "ui/hud.h"

// Encapsulates all input handling logic for the player character.
class InputHandler {
 public:
  // Process input for the given character and map.
  // Returns true if the character moved, false otherwise.
  static bool HandleInput(Character* player, class Map* map, HUD* hud);

 private:
  // Get keyboard state and compute movement delta.
  static void GetMovementInput(int& dx, int& dy, bool& is_running,
                               Direction& facing_direction);

  // Process HUD input.
  static void GetHudInput(HUD* hud);

  // Check if movement is valid (not out of bounds, no collision).
  static bool IsMovementValid(int x, int y, Map* map);
};
