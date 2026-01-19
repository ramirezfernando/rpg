#pragma once

#include "graphics/sprite_sheet_renderer.h"

class HUD {
 public:
  HUD();
  ~HUD() = default;
  void RenderInventory();

 private:
  SpriteSheetRenderer* inventory_;
};