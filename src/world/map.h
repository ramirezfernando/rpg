#pragma once

#include <array>
#include <memory>
#include <optional>
#include <vector>

#include "constants/map_constants.h"
#include "graphics/sprite.h"

// This class manages rendering of the game map using various tile sets. The map
// consists of multiple layers such as grass, water, buildings, etc. The map is
// 16x16 tiles, each tile is 48x48 pixels (scaled up by `SPRITE_SCALE` from
// 16x16).
class Map {
 public:
  Map();
  ~Map() = default;
  void RenderPlants();
  void RenderGrassDirt();
  void RenderGrassWater();
  void RenderHouse();
  void RenderWoodFence();
  void RenderClothingRack();
  void RenderMailbox();
  void RenderWaterfall();
  void RenderCliff();
  // Returns the rendering order of all the tile maps. Necessary to ensure
  // the map is rendered properly, e.g. fence rendered on top of grass.
  static const std::vector<std::array<int, Constants::MAP_ROWS_BY_COLUMNS>>
  GetOrderedTileMapLayers();
  // Returns the index of the tile found at `x`, `y` on the map. The index is
  // the position of the tile from its sprite sheet, e.g. 9 is the index of the
  // grass tile from grass_dirt.png. Since tiles can overlap, we check the top
  // most tile for collision detection.
  std::optional<int> GetTopmostTile(int x, int y);
  // Returns whether the provided `tile` causes a collision (unwalkable tile).
  bool IsCollisionTile(int tile);
  // Returns whether the provided `x`, `y` is larger than the SDL2 window size.
  bool IsOutOfBounds(int x, int y);

 private:
  Sprite* plants_;
  Sprite* grass_dirt_;
  Sprite* grass_water_;
  Sprite* house_;
  Sprite* house_chimney_smoke_;
  Sprite* wood_fence_;
  Sprite* clothing_rack_;
  Sprite* mailbox_;
  Sprite* waterfall_;
  Sprite* cliff_;
};
