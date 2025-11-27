#include "map/map_renderer.h"

#include <iostream>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

MapRenderer::MapRenderer() {
  tile_map_ = std::unique_ptr<SpriteSheetRenderer>(new SpriteSheetRenderer(
      Constants::TILE_SET_PATH, Constants::TILE_WIDTH, Constants::TILE_HEIGHT));
  if (tile_map_) {
#if defined(DEBUG_MODE)
    std::cout << "Tile map created" << std::endl;
#endif  // DEBUG_MODE
  }

  tiny_house_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/tiny_house.png", 80, 100));
  if (tiny_house_) {
#if defined(DEBUG_MODE)
    std::cout << "Tiny house created" << std::endl;
#endif  // DEBUG_MODE
  }

  wood_fence_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/wood_fence.png", 16, 16));
  if (wood_fence_) {
#if defined(DEBUG_MODE)
    std::cout << "Wood fence created" << std::endl;
#endif  // DEBUG_MODE
  }

  waterfall_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/waterfall.png", 48, 80));
  if (waterfall_) {
#if defined(DEBUG_MODE)
    std::cout << "Waterfall created" << std::endl;
#endif  // DEBUG_MODE
  }

  grass_water_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/grass_water.png", 16, 16));
  if (grass_water_) {
#if defined(DEBUG_MODE)
    std::cout << "Grass water created" << std::endl;
#endif  // DEBUG_MODE
  }

  cliff_ = std::unique_ptr<SpriteSheetRenderer>(
      new SpriteSheetRenderer("assets/sprites/map/cliff.png", 16, 16));
  if (cliff_) {
#if defined(DEBUG_MODE)
    std::cout << "Cliff created" << std::endl;
#endif  // DEBUG_MODE
  }
}

void MapRenderer::RenderGrassTiles() {
  if (tile_map_) {
    tile_map_->RenderTileMap(Constants::TILE_MAP, Constants::TILE_WIDTH,
                             Constants::TILE_HEIGHT, 0, 0);
  }
}

void MapRenderer::RenderGrassWater() {
  if (grass_water_) {
    // Sorted by dst_x (ascending), secondary sort by dst_y
    grass_water_->RenderSprite(297, /*dst_x=*/0, /*dst_y=*/0);
    grass_water_->RenderSprite(297, /*dst_x=*/0, /*dst_y=*/48);
    grass_water_->RenderSprite(297, /*dst_x=*/0, /*dst_y=*/96);
    grass_water_->RenderSprite(297, /*dst_x=*/0, /*dst_y=*/144);
    grass_water_->RenderSprite(297, /*dst_x=*/0, /*dst_y=*/192);
    grass_water_->RenderSprite(293, /*dst_x=*/0, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/0, /*dst_y=*/240);
    grass_water_->RenderSprite(344, /*dst_x=*/0, /*dst_y=*/240);
    grass_water_->RenderSprite(297, /*dst_x=*/48, /*dst_y=*/144);
    grass_water_->RenderSprite(297, /*dst_x=*/48, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/48, /*dst_y=*/240);
    grass_water_->RenderSprite(345, /*dst_x=*/48, /*dst_y=*/240);
    grass_water_->RenderSprite(297, /*dst_x=*/96, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/96, /*dst_y=*/240);
    grass_water_->RenderSprite(345, /*dst_x=*/96, /*dst_y=*/240);
    grass_water_->RenderSprite(297, /*dst_x=*/144, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/144, /*dst_y=*/240);
    grass_water_->RenderSprite(345, /*dst_x=*/144, /*dst_y=*/240);
    grass_water_->RenderSprite(297, /*dst_x=*/192, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/192, /*dst_y=*/240);
    grass_water_->RenderSprite(345, /*dst_x=*/192, /*dst_y=*/240);
    grass_water_->RenderSprite(297, /*dst_x=*/240, /*dst_y=*/144);
    grass_water_->RenderSprite(297, /*dst_x=*/240, /*dst_y=*/192);
    grass_water_->RenderSprite(294, /*dst_x=*/240, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/240, /*dst_y=*/240);
    grass_water_->RenderSprite(347, /*dst_x=*/240, /*dst_y=*/240);
    grass_water_->RenderSprite(297, /*dst_x=*/288, /*dst_y=*/144);
    grass_water_->RenderSprite(297, /*dst_x=*/288, /*dst_y=*/192);
    grass_water_->RenderSprite(345, /*dst_x=*/288, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/336, /*dst_y=*/96);
    grass_water_->RenderSprite(297, /*dst_x=*/336, /*dst_y=*/144);
    grass_water_->RenderSprite(297, /*dst_x=*/336, /*dst_y=*/192);
    grass_water_->RenderSprite(345, /*dst_x=*/336, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/384, /*dst_y=*/0);
    grass_water_->RenderSprite(297, /*dst_x=*/384, /*dst_y=*/48);
    grass_water_->RenderSprite(294, /*dst_x=*/384, /*dst_y=*/48);
    grass_water_->RenderSprite(297, /*dst_x=*/384, /*dst_y=*/96);
    grass_water_->RenderSprite(299, /*dst_x=*/384, /*dst_y=*/96);
    grass_water_->RenderSprite(297, /*dst_x=*/384, /*dst_y=*/144);
    grass_water_->RenderSprite(299, /*dst_x=*/384, /*dst_y=*/144);
    grass_water_->RenderSprite(297, /*dst_x=*/384, /*dst_y=*/192);
    grass_water_->RenderSprite(347, /*dst_x=*/384, /*dst_y=*/192);
    grass_water_->RenderSprite(297, /*dst_x=*/432, /*dst_y=*/0);
    grass_water_->RenderSprite(297, /*dst_x=*/432, /*dst_y=*/48);
    grass_water_->RenderSprite(345, /*dst_x=*/432, /*dst_y=*/48);
    grass_water_->RenderSprite(297, /*dst_x=*/480, /*dst_y=*/0);
    grass_water_->RenderSprite(299, /*dst_x=*/480, /*dst_y=*/0);
    grass_water_->RenderSprite(297, /*dst_x=*/480, /*dst_y=*/48);
  }
}

void MapRenderer::RenderWoodFence() {
  if (wood_fence_) {
    // Sorted by dst_x (ascending), secondary sort by dst_y
    wood_fence_->RenderSprite(13, /*dst_x=*/0, /*dst_y=*/302);
    wood_fence_->RenderSprite(10, /*dst_x=*/136, /*dst_y=*/302);
    wood_fence_->RenderSprite(11, /*dst_x=*/184, /*dst_y=*/302);
    wood_fence_->RenderSprite(1, /*dst_x=*/232, /*dst_y=*/302);
    wood_fence_->RenderSprite(0, /*dst_x=*/280, /*dst_y=*/206);
    wood_fence_->RenderSprite(3, /*dst_x=*/280, /*dst_y=*/254);
    wood_fence_->RenderSprite(13, /*dst_x=*/280, /*dst_y=*/302);
    wood_fence_->RenderSprite(7, /*dst_x=*/328, /*dst_y=*/206);
    wood_fence_->RenderSprite(7, /*dst_x=*/376, /*dst_y=*/206);
    wood_fence_->RenderSprite(11, /*dst_x=*/424, /*dst_y=*/206);
    wood_fence_->RenderSprite(10, /*dst_x=*/424, /*dst_y=*/446);
    wood_fence_->RenderSprite(7, /*dst_x=*/472, /*dst_y=*/446);
    wood_fence_->RenderSprite(7, /*dst_x=*/520, /*dst_y=*/446);
    wood_fence_->RenderSprite(7, /*dst_x=*/568, /*dst_y=*/446);
    wood_fence_->RenderSprite(10, /*dst_x=*/616, /*dst_y=*/206);
    wood_fence_->RenderSprite(7, /*dst_x=*/616, /*dst_y=*/446);
    wood_fence_->RenderSprite(2, /*dst_x=*/664, /*dst_y=*/206);
    wood_fence_->RenderSprite(3, /*dst_x=*/664, /*dst_y=*/254);
    wood_fence_->RenderSprite(3, /*dst_x=*/664, /*dst_y=*/302);
    wood_fence_->RenderSprite(3, /*dst_x=*/664, /*dst_y=*/350);
    wood_fence_->RenderSprite(3, /*dst_x=*/664, /*dst_y=*/398);
    wood_fence_->RenderSprite(8, /*dst_x=*/664, /*dst_y=*/446);
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