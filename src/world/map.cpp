#include "map.h"

#include <array>
#include <cstddef>
#include <optional>
#include <ranges>
#include <vector>

#include "cache/cache.h"
#include "constants/entity_constants.h"
#include "constants/game_constants.h"
#include "constants/map_constants.h"
#include "constants/sprite_constants.h"
#include "graphics/sprite.h"
#include "util/math.h"

Map::Map() {
  Cache* cache = Cache::GetInstance();

  plants_ = cache->GetOrCreateSpriteSheet(
      Constants::PLANTS_FILE_PATH,
      Sprite::Dimension{.width = Constants::SPRITE_WIDTH,
                        .height = Constants::SPRITE_HEIGHT});

  grass_dirt_ = cache->GetOrCreateSpriteSheet(
      Constants::GRASS_AND_DIRT_FILE_PATH,
      Sprite::Dimension{.width = Constants::SPRITE_WIDTH,
                        .height = Constants::SPRITE_HEIGHT});

  house_ = cache->GetOrCreateSpriteSheet(
      Constants::HOUSE_FILE_PATH,
      Sprite::Dimension{.width = Constants::HOUSE_WIDTH,
                        .height = Constants::HOUSE_HEIGHT});

  house_chimney_smoke_ = cache->GetOrCreateSpriteSheet(
      Constants::HOUSE_CHIMNEY_SMOKE_FILE_PATH,
      Sprite::Dimension{.width = Constants::HOUSE_CHIMNEY_SMOKE_WIDTH,
                        .height = Constants::HOUSE_CHIMNEY_SMOKE_HEIGHT});

  wood_fence_ = cache->GetOrCreateSpriteSheet(
      Constants::WOOD_FENCE_FILE_PATH,
      Sprite::Dimension{.width = Constants::SPRITE_WIDTH,
                        .height = Constants::SPRITE_HEIGHT});

  clothing_rack_ = cache->GetOrCreateSpriteSheet(
      Constants::CLOTHING_RACK_FILE_PATH,
      Sprite::Dimension{.width = Constants::CLOTHING_RACK_WIDTH,
                        .height = Constants::CLOTHING_RACK_HEIGHT});

  mailbox_ = cache->GetOrCreateSpriteSheet(
      Constants::MAILBOX_FILE_PATH,
      Sprite::Dimension{.width = Constants::MAILBOX_WIDTH,
                        .height = Constants::MAILBOX_HEIGHT});

  waterfall_ = cache->GetOrCreateSpriteSheet(
      Constants::WATERFALL_FILE_PATH,
      Sprite::Dimension{.width = Constants::WATERFALL_WIDTH,
                        .height = Constants::WATERFALL_HEIGHT});

  grass_water_ = cache->GetOrCreateSpriteSheet(
      Constants::GRASS_AND_WATER_FILE_PATH,
      Sprite::Dimension{.width = Constants::SPRITE_WIDTH,
                        .height = Constants::SPRITE_HEIGHT});

  cliff_ = cache->GetOrCreateSpriteSheet(
      Constants::CLIFF_FILE_PATH,
      Sprite::Dimension{.width = Constants::SPRITE_WIDTH,
                        .height = Constants::SPRITE_HEIGHT});
}

void Map::RenderPlants() const {
  // Plants rendering not implemented yet.
  if (plants_ != nullptr) {
    plants_->RenderTileMap(Constants::TILE_MAP_PLANTS);
  }
}

void Map::RenderGrassDirt() const {
  if (grass_dirt_ != nullptr) {
    grass_dirt_->RenderTileMap(Constants::TILE_MAP_GRASS_DIRT);
  }
}

void Map::RenderGrassWater() const {
  if (grass_water_ != nullptr) {
    grass_water_->RenderTileMap(Constants::TILE_MAP_GRASS_WATER_FIRST_LAYER);
    grass_water_->RenderTileMap(Constants::TILE_MAP_GRASS_WATER_SECOND_LAYER);
  }
}

void Map::RenderWoodFence() const {
  if (wood_fence_ != nullptr) {
    wood_fence_->RenderTileMap(Constants::TILE_MAP_FENCE);
  }
}

void Map::RenderClothingRack() const {
  if (clothing_rack_ != nullptr) {
    clothing_rack_->RenderSprite(
        /*sprite_index=*/0,
        Sprite::Coordinate{.x_pos = Constants::CLOTHING_RACK_DST_X,
                           .y_pos = Constants::CLOTHING_RACK_DST_Y});
  }
}

void Map::RenderMailbox() const {
  if (mailbox_ != nullptr) {
    mailbox_->RenderSprite(
        /*sprite_index=*/0,
        Sprite::Coordinate{.x_pos = Constants::MAILBOX_DST_X,
                           .y_pos = Constants::MAILBOX_DST_Y});
  }
}

void Map::RenderHouse() const {
  if (house_ != nullptr) {
    // Renders the entire house as a single sprite, not individual 48x48 tiles.
    house_->RenderSprite(/*sprite_index=*/0,
                         Sprite::Coordinate{.x_pos = Constants::HOUSE_DST_X,
                                            .y_pos = Constants::HOUSE_DST_Y});
  }
  if (house_chimney_smoke_ != nullptr) {
    house_chimney_smoke_->RenderAnimatedSprite(
        Sprite::Coordinate{.x_pos = Constants::HOUSE_CHIMNEY_SMOKE_DST_X,
                           .y_pos = Constants::HOUSE_CHIMNEY_SMOKE_DST_Y});
  }
}

void Map::RenderWaterfall() const {
  if (waterfall_ != nullptr) {
    // Renders the entire waterfall as an animated sprite, not individual
    // animated, 48x48 tiles.
    waterfall_->RenderAnimatedSprite(
        Sprite::Coordinate{.x_pos = Constants::WATERFALL_DST_X,
                           .y_pos = Constants::WATERFALL_DST_Y});
  }
}

void Map::RenderCliff() const {
  if (cliff_ != nullptr) {
    cliff_->RenderTileMap(Constants::TILE_MAP_CLIFF);
  }
}

std::vector<std::array<int, Constants::MAP_ROWS_BY_COLUMNS>>
Map::GetOrderedTileMapLayers() {
  // Don't include all tile maps, only those that affect rendering order, i.e.
  // plants are decorative and can be ignored for rendering order.
  return {Constants::TILE_MAP_GRASS_DIRT,
          Constants::TILE_MAP_GRASS_WATER_FIRST_LAYER,
          Constants::TILE_MAP_GRASS_WATER_SECOND_LAYER,
          Constants::TILE_MAP_CLIFF, Constants::TILE_MAP_FENCE};
}

std::optional<int> Map::GetTopmostTile(Sprite::Coordinate coordinate) {
  const int index = Math::GetRowMajorOrderIndexFromCoordinates(coordinate);
  auto ordered_tile_map_layers = GetOrderedTileMapLayers();
  // Iterate in reverse order without modifying `GetOrderedTileMapLayers`.
  // Start by checking the topmost rendered tile and make your way down to
  // the bottommost rendered tile.
  for (auto tile_map : std::ranges::reverse_view(ordered_tile_map_layers)) {
    if (index >= 0) {
      auto u_index = static_cast<std::size_t>(index);
      if (u_index < tile_map.size() && tile_map.at(u_index) >= 0) {
        return tile_map.at(u_index);
      }
    }
  }
  return std::nullopt;
}

bool Map::IsCollisionTile(int tile) {
  switch (tile) {
    // Fences:
    case Constants::FENCE_TILE_AT_INDEX_0:
    case Constants::FENCE_TILE_AT_INDEX_1:
    case Constants::FENCE_TILE_AT_INDEX_2:
    case Constants::FENCE_TILE_AT_INDEX_3:
    case Constants::FENCE_TILE_AT_INDEX_7:
    case Constants::FENCE_TILE_AT_INDEX_8:
    case Constants::FENCE_TILE_AT_INDEX_10:
    case Constants::FENCE_TILE_AT_INDEX_11:
    case Constants::FENCE_TILE_AT_INDEX_13:
    // Grass water:
    case Constants::GRASS_AND_WATER_TILE_INDEX_294:
    case Constants::GRASS_AND_WATER_TILE_INDEX_297:
    case Constants::GRASS_AND_WATER_TILE_INDEX_299:
    case Constants::GRASS_AND_WATER_TILE_INDEX_345:
    case Constants::GRASS_AND_WATER_TILE_INDEX_347:
      return true;
    default:
      return false;
  }
}

bool Map::IsCollision(Sprite::Coordinate coordinate) {
  // Mailbox:
  // TODO(ramirezfernando): This is a placeholder for player and mailbox
  // bounding boxs.
  // TODO(ramirezfernando): The player has a margin around the sprite, so the
  // collisions do not truly appear like collisions.
  const auto player_box = Sprite::BoundingBox{
      .x = static_cast<float>(coordinate.x_pos),
      .y = static_cast<float>(coordinate.y_pos),
      .w = static_cast<float>(Constants::ENTITY_SPRITE_WIDTH *
                              Constants::SPRITE_SCALE),
      .h = static_cast<float>(Constants::ENTITY_SPRITE_HEIGHT *
                              Constants::SPRITE_SCALE),
  };

  return player_box.Intersects({
      .x = static_cast<float>(Constants::MAILBOX_DST_X),
      .y = static_cast<float>(Constants::MAILBOX_DST_Y),
      .w = static_cast<float>(Constants::MAILBOX_WIDTH *
                              Constants::SPRITE_SCALE),
      .h = static_cast<float>(Constants::MAILBOX_HEIGHT *
                              Constants::SPRITE_SCALE),
  });
}

bool Map::IsOutOfBounds(Sprite::Coordinate coordinate) {
  const int map_size = Constants::WINDOW_SIZE;
  return coordinate.x_pos < 0 || coordinate.x_pos >= map_size ||
         coordinate.y_pos < 0 || coordinate.y_pos >= map_size;
}