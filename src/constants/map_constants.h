#pragma once

#include <array>

namespace Constants {

extern const char* PLANTS_FILE_PATH;
extern const char* HOUSE_FILE_PATH;
extern const int HOUSE_WIDTH;
extern const int HOUSE_HEIGHT;
extern const int HOUSE_DST_X;
extern const int HOUSE_DST_Y;
extern const char* HOUSE_CHIMNEY_SMOKE_FILE_PATH;
extern const int HOUSE_CHIMNEY_SMOKE_WIDTH;
extern const int HOUSE_CHIMNEY_SMOKE_HEIGHT;
extern const int HOUSE_CHIMNEY_SMOKE_DST_X;
extern const int HOUSE_CHIMNEY_SMOKE_DST_Y;
extern const char* WOOD_FENCE_FILE_PATH;
extern const char* CLOTHING_RACK_FILE_PATH;
extern const int CLOTHING_RACK_WIDTH;
extern const int CLOTHING_RACK_HEIGHT;
extern const int CLOTHING_RACK_DST_X;
extern const int CLOTHING_RACK_DST_Y;
extern const char* MAILBOX_FILE_PATH;
extern const int MAILBOX_WIDTH;
extern const int MAILBOX_HEIGHT;
extern const int MAILBOX_DST_X;
extern const int MAILBOX_DST_Y;
extern const char* WATERFALL_FILE_PATH;
extern const int WATERFALL_WIDTH;
extern const int WATERFALL_HEIGHT;
extern const int WATERFALL_DST_X;
extern const int WATERFALL_DST_Y;
extern const char* GRASS_AND_WATER_FILE_PATH;
extern const char* GRASS_AND_DIRT_FILE_PATH;
extern const char* CLIFF_FILE_PATH;

// Number of columns in the map.
constexpr int MAP_COLUMNS = 16;

// Number of rows in the map.
constexpr int MAP_ROWS = 16;

// Number of rows * columns in the map.
constexpr int MAP_ROWS_BY_COLUMNS = MAP_ROWS * MAP_COLUMNS;

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

}  // namespace Constants