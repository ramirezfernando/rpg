#pragma once
#include "entities/entity.h"
#include "world/map.h"

namespace Movement {

// Direction and delta helpers.
void DirectionToDelta(Direction direction, int gap,
                      Sprite::Coordinate& coordinate);
bool IsMoving(Sprite::Coordinate coordinate);
bool IsMovingDiagonally(Sprite::Coordinate coordinate);

// Diagonal movement normalization.
void NormalizeDiagonalMovement(Sprite::Coordinate& coordinate, int gap);

// Returns true if movement was successful, false if blocked.
bool ApplyMovement(Entity& entity, Sprite::Coordinate coordinate,
                   Action action);

// Convenience overload for directional movement.
bool ApplyDirectionalMovement(Entity& entity, Direction direction, int gap,
                              Action action);

}  // namespace Movement
