#pragma once

#include <array>

namespace Constants {

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