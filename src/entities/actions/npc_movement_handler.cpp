#include "npc_movement_handler.h"

#include <cstdlib>
#include <optional>

#include "constants/entity_constants.h"
#include "util/logger.h"
#include "util/math.h"
#include "util/movement.h"
#include "world/map.h"

// How long the NPC stays idle or moving before deciding again.
static const int DECISION_DURATION = 80;
// Counter for how long NPC stays in current state.
static int decision_counter = 0;
// Current direction the NPC is committed to.
static Direction current_committed_direction = Direction::Down;

void NpcMovementHandler::UpdateNpcMovement(Entity* npc, Map* map) {
  if (!npc || !map) {
    Logger::Error("NpcMovementHandler", "NPC or map is null");
    return;
  }

  decision_counter++;

  // Make a new decision every DECISION_DURATION frames.
  if (decision_counter >= DECISION_DURATION) {
    decision_counter = 0;

    // 60% chance to move, 40% chance to stay idle
    if (Math::GetRandomInt(0, 99) < 60) {
      current_committed_direction = GetRandomDirection();
    }
  }

  // Try to move in committed direction.
  if (Movement::ApplyDirectionalMovement(npc, current_committed_direction,
                                         Constants::ENTITY_WALK_GAP, map,
                                         Action::Walk)) {
    npc->SetDirectionFacing(current_committed_direction);
  } else {
    // Movement was blocked or failed - entity is already set to idle by
    // `ApplyDirectionalMovement`. No additional action needed.
  }
}

Direction NpcMovementHandler::GetRandomDirection() {
  switch (Math::GetRandomInt(0, 3)) {
    case 0:
      return Direction::Up;
    case 1:
      return Direction::Down;
    case 2:
      return Direction::Left;
    case 3:
      return Direction::Right;
    default:
      return Direction::Down;
  }
}