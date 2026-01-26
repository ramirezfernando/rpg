#pragma once

#include <SDL2/SDL.h>

#include <array>

namespace Constants {

// Speed of idle animation frame changes.
extern const int CHARACTER_IDLE_ANIMATION_SPEED;
// Speed of walk and run animation frame changes.
extern const int CHARACTER_WALK_AND_RUN_ANIMATION_SPEED;
// Gap in pixels for character movement.
extern const int CHARACTER_WALK_GAP;
// Delay between frames in milliseconds.
extern const Uint32 FRAME_DELAY;
// Number of columns in the map.
constexpr int MAP_COLUMNS = 16;
// Number of rows in the map.
constexpr int MAP_ROWS = 16;
// Number of rows * columns in the map.
constexpr int MAP_ROWS_BY_COLUMNS = MAP_ROWS * MAP_COLUMNS;
// The starting X position of the player when the game starts.
extern const int PLAYER_START_X;
// The starting Y position of the player when the game starts.
extern const int PLAYER_START_Y;
// Height of each tile in pixels.
extern const int SPRITE_HEIGHT;
// Scale factor for sprites.
extern const int SPRITE_SCALE;
// Width of each tile in pixels.
extern const int SPRITE_WIDTH;
// 1D matrix representation of the tile map for the cliff sprite sheet.
extern const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_CLIFF;
// 1D matrix representation of the tile map for the fence sprite sheet.
extern const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_FENCE;
// 1D matrix representation of the tile map for the plants sprite sheet.
extern const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_PLANTS;
// 1D matrix representation of the tile map for the grass and dirt sprite sheet.
extern const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_GRASS_DIRT;
// 1D matrix representation of the first layer tile map for the grass and water
// sprite sheet.
extern const std::array<int, MAP_ROWS_BY_COLUMNS>
    TILE_MAP_GRASS_WATER_FIRST_LAYER;
// 1D matrix representation of the second layer tile map for the grass and water
// sprite sheet.
extern const std::array<int, MAP_ROWS_BY_COLUMNS>
    TILE_MAP_GRASS_WATER_SECOND_LAYER;
// The size of the SDL2 window.
extern const int WINDOW_SIZE;

}  // namespace Constants
