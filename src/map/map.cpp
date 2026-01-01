#include "map.h"

#include <array>
#include <iostream>
#include <vector>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

namespace {

static int GetIndex(int x, int y) {
  int column = x / (Constants::SPRITE_WIDTH * Constants::SPRITE_SCALE) + 1;
  int row = y / (Constants::SPRITE_HEIGHT * Constants::SPRITE_SCALE) + 1;
  return row * Constants::MAP_COLUMNS + column;
}

}  // namespace

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

  house_chimney_smoke_ =
      std::unique_ptr<SpriteSheetRenderer>(new SpriteSheetRenderer(
          "assets/sprites/map/house_chimney_smoke.png", 32, 64));
  if (house_chimney_smoke_ && house_chimney_smoke_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "House chimney smoke created" << std::endl;
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
    grass_dirt_->RenderTileMap(Constants::TILE_MAP_GRASS_DIRT,
                               Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                               /*dst_x=*/0,
                               /*dst_y=*/0);
  }
}

void Map::RenderGrassWater() {
  if (grass_water_) {
    grass_water_->RenderTileMap(Constants::TILE_MAP_GRASS_WATER_FIRST_LAYER,
                                Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                                /*dst_x=*/0,
                                /*dst_y=*/0);
    grass_water_->RenderTileMap(Constants::TILE_MAP_GRASS_WATER_SECOND_LAYER,
                                Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                                /*dst_x=*/0, /*dst_y=*/0);
  }
}

void Map::RenderWoodFence() {
  if (wood_fence_) {
    wood_fence_->RenderTileMap(Constants::TILE_MAP_FENCE,
                               Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                               /*dst_x=*/0, /*dst_y=*/0);
  }
}

void Map::RenderHouse() {
  if (house_) {
    // Renders the entire house as a single sprite, not individual 48x48 tiles.
    house_->RenderSprite(0, /*dst_x=*/432, /*dst_y=*/48);
  }
  if (house_chimney_smoke_) {
    house_chimney_smoke_->RenderAnimatedSprite(/*dst_x=*/566, /*dst_y=*/-92);
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
    cliff_->RenderTileMap(Constants::TILE_MAP_CLIFF, Constants::MAP_COLUMNS,
                          Constants::MAP_ROWS,
                          /*dst_x=*/0, /*dst_y=*/0);
  }
}

const std::vector<std::array<int, Constants::MAP_ROWS_BY_COLUMNS>>
Map::GetOrderedTileMapLayers() {
  return {Constants::TILE_MAP_GRASS_DIRT,
          Constants::TILE_MAP_GRASS_WATER_FIRST_LAYER,
          Constants::TILE_MAP_GRASS_WATER_SECOND_LAYER,
          Constants::TILE_MAP_CLIFF, Constants::TILE_MAP_FENCE};
}

std::optional<int> Map::GetTopmostTile(int x, int y) {
  int index = GetIndex(x, y);
  auto ordered_tile_map_layers = GetOrderedTileMapLayers();
  // Iterate in reverse order without modifying `GetOrderedTileMapLayers`.
  // Start by checking the topmost rendered tile and make your way down to
  // the bottommost rendered tile.
  for (auto it = ordered_tile_map_layers.rbegin();
       it != ordered_tile_map_layers.rend(); ++it) {
    auto tile_map = *it;
    if (index >= 0 && index < tile_map.size() && tile_map[index] >= 0) {
      return tile_map[index];
    }
  }
  return std::nullopt;
}

bool Map::IsCollisionTile(int tile) {
  switch (tile) {
    // Fences:
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
    case 10:
    case 11:
    case 13:
    // Grass water:
    case 294:
    case 297:
    case 299:
    case 345:
    case 347:
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