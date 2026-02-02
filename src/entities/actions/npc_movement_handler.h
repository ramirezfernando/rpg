#pragma once

#include "entities/entity.h"

// Handles random movement for NPC characters.
class NpcMovementHandler {
 public:
  // Update NPC movement.
  static void UpdateNpcMovement(Entity& npc, class Map& map);

 private:
  // Generate a random direction for the NPC to face.
  static Direction GetRandomDirection();
};
