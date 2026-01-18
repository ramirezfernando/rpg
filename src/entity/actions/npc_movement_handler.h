#pragma once

#include "entity/character.h"

// Handles random movement for NPC characters.
class NpcMovementHandler {
 public:
  // Update NPC movement.
  static void UpdateNpcMovement(Character* npc, class Map* map);

 private:
  // Generate a random direction for the NPC to face.
  static Direction GetRandomDirection();

  // Attempt to move the NPC in the given direction.
  // Returns true if movement was successful, false if blocked or invalid.
  static bool TryMove(Character* npc, Map* map, Direction direction);

  // Check if movement is valid (not out of bounds, no collision).
  static bool IsMovementValid(int x, int y, Map* map);
};
