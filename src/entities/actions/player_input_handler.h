#pragma once

#include "entities/entity.h"
#include "ui/hud.h"
#include "world/map.h"

// Encapsulates all input handling logic for the player character.
class InputHandler {
 public:
  // Process input for the given character and map.
  // Returns true if the character moved, false otherwise.
  static bool HandleInput(Entity* player, class Map* map, HUD* hud);

 private:
  // Get keyboard state and compute movement delta.
  static void GetMovementInput(int& dx, int& dy, bool& is_running,
                               Direction& facing_direction);

  // Process HUD input.
  static void GetHudInput(HUD* hud);
};
