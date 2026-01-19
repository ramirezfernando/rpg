#include "npc_movement_handler.h"

#include <cstdlib>
#include <optional>

#include "graphics/map.h"
#include "util/constants.h"
#include "util/logger.h"

// How often the NPC decides to move (in frames).
static const int MOVEMENT_FREQUENCY = 100;
// How long the NPC stays idle or moving before deciding again.
static const int DECISION_DURATION = 80;
// Counter for how long NPC stays in current state.
static int decision_counter = 0;
// Current direction the NPC is committed to.
static Direction current_committed_direction = Direction::Down;

void NpcMovementHandler::UpdateNpcMovement(Character* npc, Map* map) {
  if (!npc || !map) {
    Logger::Error("NpcMovementHandler", "NPC or map is null");
    return;
  }

  // Increment decision counter
  decision_counter++;

  // Make a new decision every DECISION_DURATION frames
  if (decision_counter >= DECISION_DURATION) {
    decision_counter = 0;

    // 60% chance to move, 40% chance to stay idle
    int random_value = rand() % 100;
    if (random_value < 60) {
      current_committed_direction = GetRandomDirection();
    }
  }

  // Try to move in committed direction
  if (TryMove(npc, map, current_committed_direction)) {
    npc->SetDirectionFacing(current_committed_direction);
    npc->SetPathForAction(Action::Walk);
    npc->IncrementAnimationFrameIndexAfterInterval();
  } else {
    // No movement or blocked: idle
    npc->SetPathForAction(Action::Idle);
    npc->IncrementAnimationFrameIndexAfterInterval();
  }
}

Direction NpcMovementHandler::GetRandomDirection() {
  int random_value = rand() % 4;
  switch (random_value) {
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

bool NpcMovementHandler::TryMove(Character* npc, Map* map,
                                 Direction direction) {
  int gap = Constants::CHARACTER_WALK_GAP;
  int dx = 0;
  int dy = 0;

  switch (direction) {
    case Direction::Up:
      dy = -gap;
      break;
    case Direction::Down:
      dy = gap;
      break;
    case Direction::Left:
      dx = -gap;
      break;
    case Direction::Right:
      dx = gap;
      break;
  }

  int new_x = npc->GetXPos() + dx;
  int new_y = npc->GetYPos() + dy;

  if (!IsMovementValid(new_x, new_y, map)) {
    return false;
  }

  npc->SetXPos(new_x);
  npc->SetYPos(new_y);
  return true;
}

bool NpcMovementHandler::IsMovementValid(int x, int y, Map* map) {
  // Check bounds.
  if (map->IsOutOfBounds(x, y)) {
    return false;
  }

  // Check collision.
  std::optional<int> tile = map->GetTopmostTile(x, y);
  if (!tile.has_value() || map->IsCollisionTile(tile.value())) {
    return false;
  }

  return true;
}
