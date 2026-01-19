#include "map.h"

#include <array>
#include <iostream>
#include <vector>

#include "graphics/sprite_sheet_renderer.h"
#include "resource/resource_manager.h"
#include "util/constants.h"

static int GetIndex(int x, int y) {
  int column = x / (Constants::SPRITE_WIDTH * Constants::SPRITE_SCALE) + 1;
  int row = y / (Constants::SPRITE_HEIGHT * Constants::SPRITE_SCALE) + 1;
  return row * Constants::MAP_COLUMNS + column;
}

Map::Map() {
  ResourceManager& rm = ResourceManager::GetInstance();

  plants_ =
      rm.GetSpriteSheet("assets/sprites/map/plants.png",
                        Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT);

  grass_dirt_ =
      rm.GetSpriteSheet("assets/sprites/map/grass_dirt.png",
                        Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT);

  house_ = rm.GetSpriteSheet("assets/sprites/map/house.png", 80, 100);

  house_chimney_smoke_ =
      rm.GetSpriteSheet("assets/sprites/map/house_chimney_smoke.png", 32, 64);

  wood_fence_ =
      rm.GetSpriteSheet("assets/sprites/map/wood_fence.png",
                        Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT);

  clothing_rack_ =
      rm.GetSpriteSheet("assets/sprites/map/clothing_rack.png", 64, 35);

  mailbox_ = rm.GetSpriteSheet("assets/sprites/map/mailbox.png", 16, 32);

  waterfall_ = rm.GetSpriteSheet("assets/sprites/map/waterfall.png", 48, 80);

  grass_water_ =
      rm.GetSpriteSheet("assets/sprites/map/grass_water.png",
                        Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT);

  cliff_ = rm.GetSpriteSheet("assets/sprites/map/cliff.png",
                             Constants::SPRITE_WIDTH, Constants::SPRITE_HEIGHT);
}

void Map::RenderPlants() {
  // Plants rendering not implemented yet.
  if (plants_) {
    plants_->RenderTileMap(Constants::TILE_MAP_PLANTS, Constants::MAP_COLUMNS,
                           Constants::MAP_ROWS,
                           /*dst_x=*/0, /*dst_y=*/0);
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

void Map::RenderClothingRack() {
  if (clothing_rack_) {
    clothing_rack_->RenderSprite(0, /*dst_x=*/330, /*dst_y=*/262);
  }
}

void Map::RenderMailbox() {
  if (mailbox_) {
    mailbox_->RenderSprite(0, /*dst_x=*/630, /*dst_y=*/236);
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
  // Don't include all tile maps, only those that affect rendering order, i.e.
  // plants are decorative and can be ignored for rendering order.
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
  // Add padding to take character dimensions into account.
  if (x < -30 || x >= Constants::WINDOW_SIZE - 60 || y < -30 ||
      y >= Constants::WINDOW_SIZE - 72) {
    return true;
  }
  return false;
}