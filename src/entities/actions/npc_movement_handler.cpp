#include "npc_movement_handler.h"

#include <cstdlib>
#include <utility>

#include "constants/entity_constants.h"
#include "entities/entity.h"
#include "util/math.h"
#include "util/movement.h"

Direction NpcMovementHandler::current_committed_direction_ = Direction::Down;
int NpcMovementHandler::decision_counter_ = 0;

void NpcMovementHandler::UpdateNpcMovement(Entity& npc) {
  decision_counter_++;

  // Make a new decision every `DECISION_DURATION` frames, in other words, how
  // long the NPC stays in its current state (idle or moving in a direction).
  if (decision_counter_ >= Constants::DECISION_DURATION) {
    decision_counter_ = 0;

    // 60% chance to move, 40% chance to stay idle
    if (Math::GetRandomInt(0, Constants::RANDOM_INT_UPPER_BOUND) <
        Constants::MOVE_PROBABILITY_PERCENT) {
      current_committed_direction_ = GetRandomDirection();
    }
  }

  // Try to move in committed direction.
  if (Movement::ApplyDirectionalMovement(npc, current_committed_direction_,
                                         Constants::ENTITY_WALK_GAP,
                                         Action::Walk)) {
    npc.SetDirectionFacing(current_committed_direction_);
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
      std::unreachable();
  }
}