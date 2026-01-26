#pragma once

#include "graphics/sprite_sheet_renderer.h"

class HUD {
 public:
  HUD();
  ~HUD() = default;
  void RenderHotBar();
  void SetSelectedSlot(int slot) { selected_slot_ = slot; }

 private:
  SpriteSheetRenderer* hotbar_;
  SpriteSheetRenderer* hotbar_select_tile_;
  SpriteSheetRenderer* hotbar_select_border_;
  int selected_slot_;
};