#pragma once

#include <memory>
#include "sprite/sprite_sheet_renderer.h"

class MapRenderer {
 public:
  MapRenderer();
  ~MapRenderer() = default;
  void RenderGrassTiles();
  void RenderGrassWater();
  void RenderTinyHouse();
  void RenderWoodFence();
  void RenderWaterfall();
  void RenderCliff();

 private:
  // Order of rendering matters: first rendered = back, last rendered = front
  std::unique_ptr<SpriteSheetRenderer> tile_map_;
  std::unique_ptr<SpriteSheetRenderer> tiny_house_;
  std::unique_ptr<SpriteSheetRenderer> wood_fence_;
  std::unique_ptr<SpriteSheetRenderer> grass_water_;
  std::unique_ptr<SpriteSheetRenderer> waterfall_;
  std::unique_ptr<SpriteSheetRenderer> cliff_;
};