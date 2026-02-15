#include "movement.h"

#include <cmath>
#include <optional>

#include "entities/entity.h"
#include "graphics/sprite.h"
#include "world/map.h"

namespace {

bool IsMovementValid(Sprite::Coordinate coordinate) {
  // Check bounds.
  if (Map::IsOutOfBounds(coordinate)) {
    return false;
  }

  // Check collision by coordinate.
  if (Map::IsCollision(coordinate)) {
    return false;
  }

  // Check collision by tile.
  std::optional<int> tile = Map::GetTopmostTile(coordinate);
  return tile.has_value() && !Map::IsCollisionTile(tile.value());
}

}  // anonymous namespace

namespace Movement {

void DirectionToDelta(Direction direction, int gap,
                      Sprite::Coordinate& coordinate) {
  coordinate.x_pos = 0;
  coordinate.y_pos = 0;

  switch (direction) {
    case Direction::Up:
      coordinate.y_pos = -gap;
      break;
    case Direction::Down:
      coordinate.y_pos = gap;
      break;
    case Direction::Left:
      coordinate.x_pos = -gap;
      break;
    case Direction::Right:
      coordinate.x_pos = gap;
      break;
  }
}

bool IsMoving(Sprite::Coordinate coordinate) {
  return coordinate.x_pos != 0 || coordinate.y_pos != 0;
}

bool IsMovingDiagonally(Sprite::Coordinate coordinate) {
  return coordinate.x_pos != 0 && coordinate.y_pos != 0;
}

void NormalizeDiagonalMovement(Sprite::Coordinate& coordinate, int gap) {
  const double hypotenuse = std::hypot(static_cast<double>(coordinate.x_pos),
                                       static_cast<double>(coordinate.y_pos));
  const double factor = static_cast<double>(gap) / hypotenuse;
  coordinate.x_pos = static_cast<int>(std::round(coordinate.x_pos * factor));
  coordinate.y_pos = static_cast<int>(std::round(coordinate.y_pos * factor));
}

bool ApplyMovement(Entity& entity, Sprite::Coordinate coordinate,
                   Action action) {
  Sprite::Coordinate new_current = entity.GetCoordinate();
  new_current.x_pos += coordinate.x_pos;
  new_current.y_pos += coordinate.y_pos;

  // Validate movement.
  if (!IsMovementValid(new_current)) {
    entity.SetPathForAction(Action::Idle);
    entity.IncrementAnimationFrameIndexAfterInterval();
    return false;
  }

  // Apply movement.
  entity.SetCoordinate(new_current);
  entity.SetPathForAction(action);
  entity.IncrementAnimationFrameIndexAfterInterval();

  return true;
}

bool ApplyDirectionalMovement(Entity& entity, Direction direction, int gap,
                              Action action) {
  Sprite::Coordinate coordinate{.x_pos = 0, .y_pos = 0};
  DirectionToDelta(direction, gap, coordinate);
  return ApplyMovement(entity, coordinate, action);
}

}  // namespace Movement