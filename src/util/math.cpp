#include "math.h"

#include "constants.h"

int Math::GetRowMajorOrderIndex(int row, int column) {
  return row * Constants::MAP_COLUMNS + column;
}

int Math::GetRowMajorOrderIndexFromCoordinates(int x, int y) {
  // Normalizes coordinates on the screen to tile map rows and columns.
  int row = y / (Constants::SPRITE_HEIGHT * Constants::SPRITE_SCALE) + 1;
  int column = x / (Constants::SPRITE_WIDTH * Constants::SPRITE_SCALE) + 1;
  return GetRowMajorOrderIndex(row, column);
}