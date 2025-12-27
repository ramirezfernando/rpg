#pragma once

#include <array>
#include <memory>
#include <vector>

#include "constants/constants.h"
#include "sprite/sprite_sheet_renderer.h"

// This class manages rendering of the game map using various tile sets. The map
// consists of multiple layers such as grass, water, buildings, etc. The map is
// 16x16 tiles, each tile is 48x48 pixels (scaled up by SPRITE_SCALE from 16x16).
class Map {
 public:
  Map();
  ~Map() = default;
  void RenderGrassDirt();
  void RenderGrassWater();
  void RenderHouse();
  void RenderWoodFence();
  void RenderWaterfall();
  void RenderCliff();
  int GetTopmostTile(int x, int y);
  bool IsCollisionTile(int tile);

 private:
  std::unique_ptr<SpriteSheetRenderer> grass_dirt_;
  std::unique_ptr<SpriteSheetRenderer> house_;
  std::unique_ptr<SpriteSheetRenderer> wood_fence_;
  std::unique_ptr<SpriteSheetRenderer> grass_water_;
  std::unique_ptr<SpriteSheetRenderer> waterfall_;
  std::unique_ptr<SpriteSheetRenderer> cliff_;
};
