#include "math.h"  // NOLINT(modernize-deprecated-headers)

#include <random>

#include "constants/map_constants.h"
#include "constants/sprite_constants.h"
#include "graphics/sprite.h"

namespace Math {

int GetRandomInt(int min, int max) {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}

int GetRowMajorOrderIndex(int row, int column) {
  return (row * Constants::MAP_COLUMNS) + column;
}

int GetRowMajorOrderIndexFromCoordinates(Sprite::Coordinate coordinate) {
  // Normalizes coordinates on the screen to tile map rows and columns.
  const int row = (coordinate.y_pos /
                   (Constants::SPRITE_HEIGHT * Constants::SPRITE_SCALE)) +
                  1;
  const int column =
      (coordinate.x_pos / (Constants::SPRITE_WIDTH * Constants::SPRITE_SCALE)) +
      1;
  return GetRowMajorOrderIndex(row, column);
}

}  // namespace Math