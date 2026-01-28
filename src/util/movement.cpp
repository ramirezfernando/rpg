#include "movement.h"

#include <cmath>
#include <optional>

#include "util/logger.h"

namespace Movement {

bool IsMovementValid(int x, int y, Map* map) {
  if (!map) {
    Logger::Error("Movement", "Map is null");
    return false;
  }

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

void DirectionToDelta(Direction direction, int gap, int& dx, int& dy) {
  dx = 0;
  dy = 0;

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
}

bool IsMoving(int dx, int dy) {
  return dx != 0 || dy != 0;
}

bool IsMovingDiagonally(int dx, int dy) {
  return dx != 0 && dy != 0;
}

void NormalizeDiagonalMovement(int& dx, int& dy, int gap) {
  double hypotenuse =
      std::hypot(static_cast<double>(dx), static_cast<double>(dy));
  double factor = static_cast<double>(gap) / hypotenuse;
  dx = static_cast<int>(std::round(dx * factor));
  dy = static_cast<int>(std::round(dy * factor));
}

bool ApplyMovement(Entity* entity, int dx, int dy, Map* map, Action action) {
  if (!entity) {
    Logger::Error(" Movement", "Entity is null");
    return false;
  }

  // Calculate new position.
  int new_x = entity->GetXPos() + dx;
  int new_y = entity->GetYPos() + dy;

  // Validate movement.
  if (!IsMovementValid(new_x, new_y, map)) {
    entity->SetPathForAction(Action::Idle);
    entity->IncrementAnimationFrameIndexAfterInterval();
    return false;
  }

  // Apply movement.
  entity->SetXPos(new_x);
  entity->SetYPos(new_y);
  entity->SetPathForAction(action);
  entity->IncrementAnimationFrameIndexAfterInterval();

  return true;
}

bool ApplyDirectionalMovement(Entity* entity, Direction direction, int gap,
                              Map* map, Action action) {
  int dx, dy;
  DirectionToDelta(direction, gap, dx, dy);
  return ApplyMovement(entity, dx, dy, map, action);
}

}  // namespace Movement