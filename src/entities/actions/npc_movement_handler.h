#pragma once

#include "entities/entity.h"

// Handles random movement for NPC characters.
class NpcMovementHandler {
 public:
  // Update NPC movement.
  static void UpdateNpcMovement(Entity& npc);

 private:
  // Generate a random direction for the NPC to face.
  static Direction GetRandomDirection();

  // Current direction the NPC is committed to.
  static Direction current_committed_direction_;

  // Counter for how long NPC stays in current state.
  static int decision_counter_;
};
