#include "constants.h"

namespace Constants {
const int FRAME_DELAY =
    1000 / 30;  // The number of milliseconds in a second divided by FPS
const int WINDOW_SIZE = 768;    // The size of the GUI window (736 x 736)
const int CHARACTER_SIZE = 64;  // The size of the character (64 x 64)
const int CHARACTER_MOVEMENT_GAP =
    20;  // The number of pixels to move the character
const int ATTACK_RANGE = 100;
const char* CHARACTER_ELF_DOWN_FOLDER_PATH = "assets/characters/elf/down/";
const char* CHARACTER_ELF_LEFT_FOLDER_PATH = "assets/characters/elf/left/";
const char* CHARACTER_ELF_RIGHT_FOLDER_PATH = "assets/characters/elf/right/";
const char* CHARACTER_ELF_UP_FOLDER_PATH = "assets/characters/elf/up/";
const char* TILE_SET_PATH = "assets/map/tile_set.png";
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int SPRITE_SCALE = 3;
// clang-format off
const int FULL_MAP[16 * 16] = {
  // row 0
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 1
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 2
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 3
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 4
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 5
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 6
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 7
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 8
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 9
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 10
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 11
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 12
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 13
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 14
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 15
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};
// clang-format on
}  // namespace Constants