#pragma once

namespace Constants {

// Number of milliseconds in a second.
extern const int MILISECONDS_PER_SECOND;
// Frames per second.
extern const int FRAME_RATE;
// Delay between frames in milliseconds.
extern const int FRAME_DELAY;
// The size of the GUI window (768 x 768).
extern const int WINDOW_SIZE;
// Gap in pixels for character movement.
extern const int CHARACTER_WALK_GAP;
// Number of rows in the map (16).
extern const int MAP_ROWS;
// Number of columns in the map (16).
extern const int MAP_COLUMNS;
// Path to the grass and dirt tile set image.
extern const char* GRASS_DIRT_TILE_SET_PATH;
// Tile map for the grass and dirt tile set.
extern const int GRASS_DIRT_TILE_MAP[];
// Tile map for the first layer of grass and water.
extern const int GRASS_WATER_TILE_MAP_FIRST_LAYER[];
// Tile map for the second layer of grass and water.
extern const int GRASS_WATER_TILE_MAP_SECOND_LAYER[];

}  // namespace Constants