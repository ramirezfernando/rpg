#pragma once

#include "entities/entity.h"
#include "world/map.h"

namespace Movement {

// Movement validation.
bool IsMovementValid(int x, int y, Map* map);

// Direction and delta helpers.
void DirectionToDelta(Direction direction, int gap, int& dx, int& dy);
bool IsMoving(int dx, int dy);
bool IsMovingDiagonally(int dx, int dy);

// Diagonal movement normalization.
void NormalizeDiagonalMovement(int& dx, int& dy, int gap);

// Returns true if movement was successful, false if blocked.
bool ApplyMovement(Entity& entity, int dx, int dy, Map& map, Action action);

// Convenience overload for directional movement.
bool ApplyDirectionalMovement(Entity& entity, Direction direction, int gap,
                              Map& map, Action action);

}  // namespace Movement
