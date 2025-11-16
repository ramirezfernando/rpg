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
const char* MAP_TILE_SET_PATH = "assets/map/tile_set.png";
const int MAP_TILE_WIDTH = 16;
const int MAP_TILE_HEIGHT = 16;
const int SPRITE_SCALE = 3;
}  // namespace Constants