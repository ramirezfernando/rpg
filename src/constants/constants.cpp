#include "constants.h"

namespace Constants {
const int FRAME_DELAY =
    1000 / 30;  // The number of milliseconds in a second divided by FPS
const int WINDOW_SIZE = 768;  // The size of the GUI window (768 x 768)
const int CHARACTER_MOVEMENT_GAP =
    20;  // The number of pixels to move the character
const char* TILE_SET_PATH = "assets/sprites/map/tile_set.png";
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
// TODO: Map only contains grass and dirt tiles, may need to expand later. `-1`
// represents empty tile and a positive integer represents the index of the tile
// in `tile_set.png`.
// clang-format off
const int TILE_MAP[TILE_WIDTH * TILE_HEIGHT] = {
  // row 0
  -1,-1,-1,-1,-1,9,9,-1,-1,-1,-1,9,9,9,9,9,
  // row 1
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,9,9,9,
  // row 2
  -1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,9,9,9,9,
  // row 3
  -1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,9,9,9,9,
  // row 4
  -1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,9,9,9,9,
  // row 5
  -1,-1,-1,-1,-1,-1,9,9,9,9,9,9,9,9,9,9,
  // row 6
  9,9,9,9,9,9,9,9,9,9,9,32,35,9,9,9,
  // row 7
  9,9,9,9,9,9,9,32,34,34,34,41,43,9,9,9,
  // row 8
  9,9,9,9,32,34,34,37,45,45,45,45,47,9,9,9,
  // row 9
  9,9,9,9,44,45,45,47,9,9,9,9,9,9,9,9,
  // row 10
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 11
  34,34,34,35,9,9,9,9,9,9,9,32,34,34,34,34,
  // row 12
  41,41,41,43,9,9,9,9,9,9,32,37,45,45,45,45,
  // row 13
  45,45,45,42,34,34,34,34,34,34,41,43,9,9,9,9,
  // row 14
  9,9,9,44,45,45,45,45,45,45,45,47,9,9,9,9,
  // row 15
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};
// clang-format on
}  // namespace Constants