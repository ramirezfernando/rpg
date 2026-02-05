#include "map.h"

#include <array>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

#include "cache/cache.h"
#include "constants/game_constants.h"
#include "constants/map_constants.h"
#include "constants/sprite_constants.h"
#include "graphics/sprite.h"
#include "util/math.h"

Map::Map() {
  Cache* cache = Cache::GetInstance();

  plants_ = cache->GetOrCreateSpriteSheet(Constants::PLANTS_FILE_PATH,
                                          Constants::SPRITE_WIDTH,
                                          Constants::SPRITE_HEIGHT);

  grass_dirt_ = cache->GetOrCreateSpriteSheet(
      Constants::GRASS_AND_DIRT_FILE_PATH, Constants::SPRITE_WIDTH,
      Constants::SPRITE_HEIGHT);

  house_ = cache->GetOrCreateSpriteSheet(Constants::HOUSE_FILE_PATH,
                                         Constants::HOUSE_WIDTH,
                                         Constants::HOUSE_HEIGHT);

  house_chimney_smoke_ =
      cache->GetOrCreateSpriteSheet(Constants::HOUSE_CHIMNEY_SMOKE_FILE_PATH,
                                    Constants::HOUSE_CHIMNEY_SMOKE_WIDTH,
                                    Constants::HOUSE_CHIMNEY_SMOKE_HEIGHT);

  wood_fence_ = cache->GetOrCreateSpriteSheet(Constants::WOOD_FENCE_FILE_PATH,
                                              Constants::SPRITE_WIDTH,
                                              Constants::SPRITE_HEIGHT);

  clothing_rack_ = cache->GetOrCreateSpriteSheet(
      Constants::CLOTHING_RACK_FILE_PATH, Constants::CLOTHING_RACK_WIDTH,
      Constants::CLOTHING_RACK_HEIGHT);

  mailbox_ = cache->GetOrCreateSpriteSheet(Constants::MAILBOX_FILE_PATH,
                                           Constants::MAILBOX_WIDTH,
                                           Constants::MAILBOX_HEIGHT);

  waterfall_ = cache->GetOrCreateSpriteSheet(Constants::WATERFALL_FILE_PATH,
                                             Constants::WATERFALL_WIDTH,
                                             Constants::WATERFALL_HEIGHT);

  grass_water_ = cache->GetOrCreateSpriteSheet(
      Constants::GRASS_AND_WATER_FILE_PATH, Constants::SPRITE_WIDTH,
      Constants::SPRITE_HEIGHT);

  cliff_ = cache->GetOrCreateSpriteSheet(Constants::CLIFF_FILE_PATH,
                                         Constants::SPRITE_WIDTH,
                                         Constants::SPRITE_HEIGHT);
}

void Map::RenderPlants() {
  // Plants rendering not implemented yet.
  if (plants_) {
    plants_->RenderTileMap(Constants::TILE_MAP_PLANTS);
  }
}

void Map::RenderGrassDirt() {
  if (grass_dirt_) {
    grass_dirt_->RenderTileMap(Constants::TILE_MAP_GRASS_DIRT);
  }
}

void Map::RenderGrassWater() {
  if (grass_water_) {
    grass_water_->RenderTileMap(Constants::TILE_MAP_GRASS_WATER_FIRST_LAYER);
    grass_water_->RenderTileMap(Constants::TILE_MAP_GRASS_WATER_SECOND_LAYER);
  }
}

void Map::RenderWoodFence() {
  if (wood_fence_) {
    wood_fence_->RenderTileMap(Constants::TILE_MAP_FENCE);
  }
}

void Map::RenderClothingRack() {
  if (clothing_rack_) {
    clothing_rack_->RenderSprite(/*sprite_index=*/0,
                                 /*dst_x=*/Constants::CLOTHING_RACK_DST_X,
                                 /*dst_y=*/Constants::CLOTHING_RACK_DST_Y);
  }
}

void Map::RenderMailbox() {
  if (mailbox_) {
    mailbox_->RenderSprite(/*sprite_index=*/0,
                           /*dst_x=*/Constants::MAILBOX_DST_X,
                           /*dst_y=*/Constants::MAILBOX_DST_Y);
  }
}

void Map::RenderHouse() {
  if (house_) {
    // Renders the entire house as a single sprite, not individual 48x48 tiles.
    house_->RenderSprite(/*sprite_index=*/0, /*dst_x=*/Constants::HOUSE_DST_X,
                         /*dst_y=*/Constants::HOUSE_DST_Y);
  }
  if (house_chimney_smoke_) {
    house_chimney_smoke_->RenderAnimatedSprite(
        /*dst_x=*/Constants::HOUSE_CHIMNEY_SMOKE_DST_X,
        /*dst_y=*/Constants::HOUSE_CHIMNEY_SMOKE_DST_Y);
  }
}

void Map::RenderWaterfall() {
  if (waterfall_) {
    // Renders the entire waterfall as an animated sprite, not individual
    // animated, 48x48 tiles.
    waterfall_->RenderAnimatedSprite(/*dst_x=*/Constants::WATERFALL_DST_X,
                                     /*dst_y=*/Constants::WATERFALL_DST_Y);
  }
}

void Map::RenderCliff() {
  if (cliff_) {
    cliff_->RenderTileMap(Constants::TILE_MAP_CLIFF);
  }
}

const std::vector<std::array<int, Constants::MAP_ROWS_BY_COLUMNS>>
Map::GetOrderedTileMapLayers() {
  // Don't include all tile maps, only those that affect rendering order, i.e.
  // plants are decorative and can be ignored for rendering order.
  return {Constants::TILE_MAP_GRASS_DIRT,
          Constants::TILE_MAP_GRASS_WATER_FIRST_LAYER,
          Constants::TILE_MAP_GRASS_WATER_SECOND_LAYER,
          Constants::TILE_MAP_CLIFF, Constants::TILE_MAP_FENCE};
}

std::optional<int> Map::GetTopmostTile(int x, int y) {
  int index = Math::GetRowMajorOrderIndexFromCoordinates(x, y);
  auto ordered_tile_map_layers = GetOrderedTileMapLayers();
  // Iterate in reverse order without modifying `GetOrderedTileMapLayers`.
  // Start by checking the topmost rendered tile and make your way down to
  // the bottommost rendered tile.
  for (auto tile_map : std::ranges::reverse_view(ordered_tile_map_layers)) {
    if (index >= 0) {
      auto u_index = static_cast<std::size_t>(index);
      if (u_index < tile_map.size() && tile_map.at(u_index) >= 0) {
        return tile_map[u_index];
      }
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
  // Add padding to take character dimensions into account.
  if (x < -30 || x >= Constants::WINDOW_SIZE - 60 || y < -30 ||
      y >= Constants::WINDOW_SIZE - 72) {
    return true;
  }
  return false;
}