#include "map/map_renderer.h"

#include <iostream>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

MapRenderer::MapRenderer() {
  tile_map_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer(Constants::GRASS_DIRT_TILE_SET_PATH,
                              Constants::MAP_ROWS, Constants::MAP_COLUMNS));
  if (tile_map_ && tile_map_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Tile map created" << std::endl;
#endif  // DEBUG_MODE
  }

  tiny_house_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/tiny_house.png", 80, 100));
  if (tiny_house_ && tiny_house_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Tiny house created" << std::endl;
#endif  // DEBUG_MODE
  }

  wood_fence_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/wood_fence.png", 16, 16));
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

  grass_water_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/grass_water.png", 16, 16));
  if (grass_water_ && grass_water_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Grass water created" << std::endl;
#endif  // DEBUG_MODE
  }

  cliff_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/cliff.png", 16, 16));
  if (cliff_ && cliff_->LoadSpriteSheet()) {
#if defined(DEBUG_MODE)
    std::cout << "Cliff created" << std::endl;
#endif  // DEBUG_MODE
  }
}

void MapRenderer::RenderGrassTiles() {
  if (tile_map_) {
    tile_map_->RenderTileMap(Constants::GRASS_DIRT_TILE_MAP,
                             Constants::MAP_ROWS, Constants::MAP_COLUMNS, 0, 0);
  }
}

void MapRenderer::RenderGrassWater() {
  if (grass_water_) {
    grass_water_->RenderTileMap(Constants::GRASS_WATER_TILE_MAP_FIRST_LAYER,
                                Constants::MAP_ROWS, 6, 0, 0);
    grass_water_->RenderTileMap(Constants::GRASS_WATER_TILE_MAP_SECOND_LAYER,
                                Constants::MAP_ROWS, 6, 0, 0);
  }
}

void MapRenderer::RenderWoodFence() {
  if (wood_fence_) {
    wood_fence_->RenderTileMap(Constants::WOOD_FENCE_TILE_MAP,
                               Constants::MAP_ROWS, 11, 0, 0);
  }
}

void MapRenderer::RenderTinyHouse() {
  if (tiny_house_) {
    tiny_house_->RenderSprite(0, /*dst_x=*/424, /*dst_y=*/26);
  }
}

void MapRenderer::RenderWaterfall() {
  if (waterfall_) {
    waterfall_->RenderAnimatedSprite(/*dst_x=*/96, /*dst_y=*/0);
  }
}

void MapRenderer::RenderCliff() {
  if (cliff_) {
    // Sorted by dst_x (ascending), secondary sort by dst_y
    cliff_->RenderSprite(81, /*dst_x=*/0, /*dst_y=*/0);
    cliff_->RenderSprite(53, /*dst_x=*/48, /*dst_y=*/0);
    cliff_->RenderSprite(32, /*dst_x=*/48, /*dst_y=*/48);
    cliff_->RenderSprite(80, /*dst_x=*/48, /*dst_y=*/96);
    cliff_->RenderSprite(120, /*dst_x=*/48, /*dst_y=*/144);
    cliff_->RenderSprite(54, /*dst_x=*/240, /*dst_y=*/48);
    cliff_->RenderSprite(83, /*dst_x=*/240, /*dst_y=*/96);
    cliff_->RenderSprite(122, /*dst_x=*/240, /*dst_y=*/144);
    cliff_->RenderSprite(81, /*dst_x=*/288, /*dst_y=*/48);
    cliff_->RenderSprite(121, /*dst_x=*/288, /*dst_y=*/96);
    cliff_->RenderSprite(59, /*dst_x=*/336, /*dst_y=*/0);
    cliff_->RenderSprite(83, /*dst_x=*/336, /*dst_y=*/48);
    cliff_->RenderSprite(122, /*dst_x=*/336, /*dst_y=*/96);
  }
}