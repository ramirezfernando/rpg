#include "map.h"

#include <iostream>
#include <iterator>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

Map::Map() {
  grass_dirt_ = std::unique_ptr<SpriteSheetRenderer>(new SpriteSheetRenderer(
      "assets/sprites/map/grass_dirt.png", Constants::SPRITE_WIDTH,
      Constants::SPRITE_HEIGHT));
  if (grass_dirt_ && grass_dirt_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Tile map created" << std::endl;
#endif  // DEBUG_MODE
  }

  house_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/house.png", 80, 100));
  if (house_ && house_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "House created" << std::endl;
#endif  // DEBUG_MODE
  }

  wood_fence_ = std::unique_ptr<SpriteSheetRenderer>(new SpriteSheetRenderer(
      "assets/sprites/map/wood_fence.png", Constants::SPRITE_WIDTH,
      Constants::SPRITE_HEIGHT));
  if (wood_fence_ && wood_fence_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Wood fence created" << std::endl;
#endif  // DEBUG_MODE
  }

  waterfall_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/waterfall.png", 48, 80));
  if (waterfall_ && waterfall_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Waterfall created" << std::endl;
#endif  // DEBUG_MODE
  }

  grass_water_ = std::unique_ptr<SpriteSheetRenderer>(new SpriteSheetRenderer(
      "assets/sprites/map/grass_water.png", Constants::SPRITE_WIDTH,
      Constants::SPRITE_HEIGHT));
  if (grass_water_ && grass_water_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Grass water created" << std::endl;
#endif  // DEBUG_MODE
  }

  cliff_ = std::unique_ptr<SpriteSheetRenderer>(new SpriteSheetRenderer(
      "assets/sprites/map/cliff.png", Constants::SPRITE_WIDTH,
      Constants::SPRITE_HEIGHT));
  if (cliff_ && cliff_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Cliff created" << std::endl;
#endif  // DEBUG_MODE
  }
}

void Map::RenderGrassDirt() {
  if (grass_dirt_) {
    grass_dirt_->RenderTileMap(Constants::GRASS_DIRT_TILE_MAP,
                               Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                               /*dst_x=*/0,
                               /*dst_y=*/0);
  }
}

void Map::RenderGrassWater() {
  if (grass_water_) {
    grass_water_->RenderTileMap(Constants::GRASS_WATER_TILE_MAP_FIRST_LAYER,
                                Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                                /*dst_x=*/0,
                                /*dst_y=*/0);
    grass_water_->RenderTileMap(Constants::GRASS_WATER_TILE_MAP_SECOND_LAYER,
                                Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                                /*dst_x=*/0, /*dst_y=*/0);
  }
}

void Map::RenderWoodFence() {
  if (wood_fence_) {
    wood_fence_->RenderTileMap(Constants::WOOD_FENCE_TILE_MAP,
                               Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                               /*dst_x=*/0, /*dst_y=*/0);
  }
}

void Map::RenderHouse() {
  if (house_) {
    // Renders the entire house as a single sprite, not individual 48x48 tiles.
    house_->RenderSprite(0, /*dst_x=*/432, /*dst_y=*/48);
  }
}

void Map::RenderWaterfall() {
  if (waterfall_) {
    // Renders the entire waterfall as an animated sprite, not individual
    // animated, 48x48 tiles.
    waterfall_->RenderAnimatedSprite(/*dst_x=*/96, /*dst_y=*/0);
  }
}

void Map::RenderCliff() {
  if (cliff_) {
    cliff_->RenderTileMap(Constants::CLIFF_TILE_MAP, Constants::MAP_COLUMNS,
                          Constants::MAP_ROWS,
                          /*dst_x=*/0, /*dst_y=*/0);
  }
}

// Since tiles can overlap, we want to check from the top most tile.
std::optional<int> Map::GetTopmostTile(int x, int y) {
  int column = x / (Constants::SPRITE_WIDTH * Constants::SPRITE_SCALE) + 1;
  int row = y / (Constants::SPRITE_HEIGHT * Constants::SPRITE_SCALE) + 1;
  int index = row * Constants::MAP_COLUMNS + column;

  auto ordered_tile_maps = {Constants::WOOD_FENCE_TILE_MAP,
                            Constants::CLIFF_TILE_MAP,
                            Constants::GRASS_WATER_TILE_MAP_SECOND_LAYER,
                            Constants::GRASS_WATER_TILE_MAP_FIRST_LAYER,
                            Constants::GRASS_DIRT_TILE_MAP};

  for (const auto& tile_map : ordered_tile_maps) {
    if (index >= 0 && index < tile_map.size() && tile_map[index] >= 0) {
      return tile_map[index];
    }
  }
  return std::nullopt;
}

bool Map::IsCollisionTile(int tile) {
  switch (tile) {
    case 0:    // Fence.
    case 1:    // Fence.
    case 2:    // Fence.
    case 3:    // Fence.
    case 7:    // Fence.
    case 8:    // Fence.
    case 10:   // Fence.
    case 11:   // Fence.
    case 13:   // Fence.
    case 294:  // Bottom right grass water shore corner edge tile.
    case 297:  // Water tile.
    case 299:  // Right grass water shore corner tile.
    case 345:  // Bottom grass water shore tile.
    case 347:  // Bottom right grass water shore corner tile.
      return true;
  }
  return false;
}

bool Map::IsOutOfBounds(int x, int y) {
  if (x < 0 || x >= Constants::WINDOW_SIZE || y < 0 ||
      y >= Constants::WINDOW_SIZE) {
    return true;
  }
  return false;
}