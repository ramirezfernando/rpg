#include "map/map_renderer.h"

#include <iostream>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

MapRenderer::MapRenderer() {
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

void MapRenderer::RenderGrassDirt() {
  if (grass_dirt_) {
    grass_dirt_->RenderTileMap(Constants::GRASS_DIRT_TILE_MAP,
                               Constants::MAP_COLUMNS, Constants::MAP_ROWS,
                               /*dst_x=*/0,
                               /*dst_y=*/0);
  }
}

void MapRenderer::RenderGrassWater() {
  if (grass_water_) {
    grass_water_->RenderTileMap(Constants::GRASS_WATER_TILE_MAP_FIRST_LAYER,
                                Constants::MAP_COLUMNS, 6, /*dst_x=*/0,
                                /*dst_y=*/0);
    grass_water_->RenderTileMap(Constants::GRASS_WATER_TILE_MAP_SECOND_LAYER,
                                Constants::MAP_COLUMNS, /*tile_map_rows=*/6,
                                /*dst_x=*/0, /*dst_y=*/0);
  }
}

void MapRenderer::RenderWoodFence() {
  if (wood_fence_) {
    wood_fence_->RenderTileMap(Constants::WOOD_FENCE_TILE_MAP,
                               Constants::MAP_COLUMNS, /*tile_map_rows=*/11,
                               /*dst_x=*/0, /*dst_y=*/0);
  }
}

void MapRenderer::RenderHouse() {
  if (house_) {
    // Renders the entire house as a single sprite, not individual 48x48 tiles.
    house_->RenderSprite(0, /*dst_x=*/432, /*dst_y=*/48);
  }
}

void MapRenderer::RenderWaterfall() {
  if (waterfall_) {
    // Renders the entire waterfall as an animated sprite, not individual
    // animated, 48x48 tiles.
    waterfall_->RenderAnimatedSprite(/*dst_x=*/96, /*dst_y=*/0);
  }
}

void MapRenderer::RenderCliff() {
  if (cliff_) {
    cliff_->RenderTileMap(Constants::CLIFF_TILE_MAP, Constants::MAP_COLUMNS,
                          /*tile_map_rows=*/4,
                          /*dst_x=*/0, /*dst_y=*/0);
  }
}