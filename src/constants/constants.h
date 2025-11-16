#pragma once

namespace Constants {

extern const int FRAME_DELAY;
extern const int WINDOW_SIZE;
extern const int CHARACTER_SIZE;
extern const int CHARACTER_MOVEMENT_GAP;
extern const char* CHARACTER_ELF_DOWN_FOLDER_PATH;
extern const char* CHARACTER_ELF_LEFT_FOLDER_PATH;
extern const char* CHARACTER_ELF_RIGHT_FOLDER_PATH;
extern const char* CHARACTER_ELF_UP_FOLDER_PATH;
extern const char* TILE_SET_PATH;
extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;
extern const int SPRITE_SCALE;
extern const int TILE_MAP[];
extern const int TINY_HOUSE_WIDTH;
extern const int TINY_HOUSE_HEIGHT;
extern const int TINY_HOUSE_X_POS;
extern const int TINY_HOUSE_Y_POS;
extern const int WOOD_FENCES[];
enum class Direction { UP, DOWN, LEFT, RIGHT };

}  // namespace Constants