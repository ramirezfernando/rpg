#pragma once

#include <array>

namespace Constants {

// Number of columns in the map.
constexpr int MAP_COLUMNS = 16;

// Number of rows in the map.
constexpr int MAP_ROWS = 16;

// Number of rows * columns in the map.
constexpr int MAP_ROWS_BY_COLUMNS = MAP_ROWS * MAP_COLUMNS;

inline constexpr const char* PLANTS_FILE_PATH = "assets/sprites/map/plants.png";
inline constexpr const char* HOUSE_FILE_PATH = "assets/sprites/map/house.png";
inline constexpr const int HOUSE_WIDTH = 80;
inline constexpr const int HOUSE_HEIGHT = 100;
inline constexpr const int HOUSE_DST_X = 432;
inline constexpr const int HOUSE_DST_Y = 48;
inline constexpr const char* HOUSE_CHIMNEY_SMOKE_FILE_PATH =
    "assets/sprites/map/house_chimney_smoke.png";
inline constexpr const int HOUSE_CHIMNEY_SMOKE_WIDTH = 32;
inline constexpr const int HOUSE_CHIMNEY_SMOKE_HEIGHT = 64;
inline constexpr const int HOUSE_CHIMNEY_SMOKE_DST_X = 566;
inline constexpr const int HOUSE_CHIMNEY_SMOKE_DST_Y = -92;
inline constexpr const char* WOOD_FENCE_FILE_PATH =
    "assets/sprites/map/wood_fence.png";
inline constexpr const char* CLOTHING_RACK_FILE_PATH =
    "assets/sprites/map/clothing_rack.png";
inline constexpr const int CLOTHING_RACK_WIDTH = 64;
inline constexpr const int CLOTHING_RACK_HEIGHT = 35;
inline constexpr const int CLOTHING_RACK_DST_X = 330;
inline constexpr const int CLOTHING_RACK_DST_Y = 262;
// Refer to `assets/sprites/map/wood_fence.png` to see which tile index
// corresponds to which fence piece.
inline constexpr const int FENCE_TILE_AT_INDEX_0 = 0;
inline constexpr const int FENCE_TILE_AT_INDEX_1 = 1;
inline constexpr const int FENCE_TILE_AT_INDEX_2 = 2;
inline constexpr const int FENCE_TILE_AT_INDEX_3 = 3;
inline constexpr const int FENCE_TILE_AT_INDEX_7 = 7;
inline constexpr const int FENCE_TILE_AT_INDEX_8 = 8;
inline constexpr const int FENCE_TILE_AT_INDEX_10 = 10;
inline constexpr const int FENCE_TILE_AT_INDEX_11 = 11;
inline constexpr const int FENCE_TILE_AT_INDEX_13 = 13;
inline constexpr const char* MAILBOX_FILE_PATH =
    "assets/sprites/map/mailbox.png";
inline constexpr const int MAILBOX_WIDTH = 16;
inline constexpr const int MAILBOX_HEIGHT = 32;
inline constexpr const int MAILBOX_DST_X = 630;
inline constexpr const int MAILBOX_DST_Y = 236;
inline constexpr const char* WATERFALL_FILE_PATH =
    "assets/sprites/map/waterfall.png";
inline constexpr const int WATERFALL_WIDTH = 48;
inline constexpr const int WATERFALL_HEIGHT = 80;
inline constexpr const int WATERFALL_DST_X = 96;
inline constexpr const int WATERFALL_DST_Y = 0;
inline constexpr const char* GRASS_AND_WATER_FILE_PATH =
    "assets/sprites/map/grass_water.png";
// Refer to `assets/sprites/map/grass_water.png` to see which tile index
// corresponds to which grass/water piece.
inline constexpr const int GRASS_AND_WATER_TILE_INDEX_294 = 294;
inline constexpr const int GRASS_AND_WATER_TILE_INDEX_297 = 297;
inline constexpr const int GRASS_AND_WATER_TILE_INDEX_299 = 299;
inline constexpr const int GRASS_AND_WATER_TILE_INDEX_345 = 345;
inline constexpr const int GRASS_AND_WATER_TILE_INDEX_347 = 347;
inline constexpr const char* GRASS_AND_DIRT_FILE_PATH =
    "assets/sprites/map/grass_dirt.png";
inline constexpr const char* CLIFF_FILE_PATH = "assets/sprites/map/cliff.png";

// clang-format off
inline constexpr const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_CLIFF = {
  // row 0 (y = 0)
  81, 53, -1, -1, -1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1,
  // row 1 (y = 48)
  -1, 32, -1, -1, -1, 54, 81, 83, -1, -1, -1, -1, -1, -1, -1, -1,
  // row 2 (y = 96)
  -1, 80, -1, -1, -1, 83, 121, 122, -1, -1, -1, -1, -1, -1, -1, -1,
  // row 3 (y = 144)
  -1, 120, -1, -1, -1, 122, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  // row 4...15 unused for this tile map.
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

inline constexpr const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_FENCE = {
  // row 0 (y = 0)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 1 (y = 48)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 2 (y = 96)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 3 (y = 144)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 4 (y = 192)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 5 (y = 240)
  -1,-1,-1,-1,-1,-1, 0, 7, 7,11,-1,-1,-1,10, 2,-1,
  // row 6 (y = 288)
  -1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 3,-1,
  // row 7 (y = 336)
  -1,-1,-1,10,11, 1,13,-1,-1,-1,-1,-1,-1,-1, 3,-1,
  // row 8 (y = 384)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,
  // row 9 (y = 432)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,
  // row 10 (y = 480)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,10, 7, 7, 7, 7, 8,-1,
  // row 11...15 unused for this tile map.
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

inline constexpr const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_PLANTS = {
  // row 0 (y = 0)
  -1,-1,-1,-1,-1,2,1,-1,-1,-1,-1,-1,2,2,-1,-1,
  // row 1 (y = 48)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,5,-1,-1,
  // row 2 (y = 96)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,19,2,
  // row 3 (y = 144)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,
  // row 4 (y = 192)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,14,-1,
  // row 5 (y = 240)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,
  // row 6 (y = 288)
  -1,1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,
  // row 7 (y = 336)
  14,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,
  // row 8 (y = 384)
  4,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 9 (y = 432)
  -1,-1,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,
  // row 10 (y = 480)
  -1,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 11 (y = 528)
  -1,-1,-1,-1,-1,-1,-1,1,5,12,-1,-1,-1,-1,-1,-1,
  // row 12 (y = 576)
  -1,-1,-1,-1,-1,-1,2,1,1,2,-1,-1,-1,-1,-1,-1,
  // row 13 (y = 624)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  // row 14 (y = 672)
  2,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,1,2,
  // row 15 (y = 720)
  5,1,2,-1,-1,-1,-1,-1,1,13,-1,-1,-1,2,2,2,
};

inline constexpr const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_GRASS_DIRT = {
  // row 0 (y = 0)
  -1,-1,-1,-1,-1,9,9,-1,-1,-1,-1,9,9,9,9,9,
  // row 1 (y = 48)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,9,9,9,9,
  // row 2 (y = 96)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,9,9,9,9,9,9,9,
  // row 3 (y = 144)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,-1,9,9,9,
  // row 4 (y = 192)
  -1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,-1,9,9,9,
  // row 5 (y = 240)
  -1,-1,-1,-1,-1,-1,9,9,9,9,-1,-1,-1,9,9,9,
  // row 6 (y = 288)
  9,9,9,9,9,9,9,9,9,9,9,32,35,9,9,9,
  // row 7 (y = 336)
  9,9,9,9,9,9,9,32,34,34,34,41,43,9,9,9,
  // row 8 (y = 384)
  9,9,9,9,32,34,34,37,45,45,45,45,47,9,9,9,
  // row 9 (y = 432)
  9,9,9,9,44,45,45,47,9,9,9,9,9,9,9,9,
  // row 10 (y = 480)
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
  // row 11 (y = 528)
  34,34,34,35,9,9,9,9,9,9,9,32,34,34,34,34,
  // row 12 (y = 576)
  41,41,41,43,9,9,9,9,9,9,32,37,45,45,45,45,
  // row 13 (y = 624)
  45,45,45,42,34,34,34,34,34,34,41,43,9,9,9,9,
  // row 14 (y = 672)
  9,9,9,44,45,45,45,45,45,45,45,47,9,9,9,9,
  // row 15 (y = 720)
  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};

inline constexpr const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_GRASS_WATER_FIRST_LAYER = {
  // row 0 (y = 0)
  -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, 297, -1, -1, -1, -1, -1,
  // row 1 (y = 48)
  -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  297, 297, 297, -1, -1, -1, -1, -1,
  // row 2 (y = 96)
  -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, 297, -1,  -1,  -1, -1, -1, -1, -1,
  // row 3 (y = 144)
  -1, -1, -1,  -1,  -1,  -1, -1, -1, 297, -1,  -1,  -1, -1, -1, -1, -1,
  // row 4 (y = 192)
  297, -1, -1, -1, -1, 297, 297, 297, 297, -1,  -1,  -1, -1, -1, -1, -1,
  // row 5 (y = 240)
  297, 297, 297, 297, 297, 297, -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1,
  // row 6...15 unused for this tile map.
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

inline constexpr const std::array<int, MAP_ROWS_BY_COLUMNS> TILE_MAP_GRASS_WATER_SECOND_LAYER = {
  // row 0 (y = 0)
  297, -1,  -1,  -1,  -1,  -1,  -1,  -1,  297, 297, 299, -1, -1, -1, -1, -1,
  // row 1 (y = 48)
  297, -1,  -1,  -1,  -1,  -1,  -1,  -1,  294, 345, 347, -1, -1, -1, -1, -1,
  // row 2 (y = 96)
  297, -1,  -1,  -1,  -1,  -1,  -1,  297, 299, -1,  -1,  -1, -1, -1, -1, -1,
  // row 3 (y = 144)
  297, 297, -1,  -1,  -1,  297, 297, 297, 299, -1,  -1,  -1, -1, -1, -1, -1,
  // row 4 (y = 192)
  293, 297, 297, 297, 297, 294, 345, 345, 347, -1,  -1,  -1, -1, -1, -1, -1,
  // row 5 (y = 240)
  344, 345, 345, 345, 345, 347, -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1,
  // row 6...15 unused for this tile map.
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};
// clang-format on

}  // namespace Constants