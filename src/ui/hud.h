#pragma once

#include "graphics/sprite.h"

class HUD {
 public:
  HUD();
  ~HUD() = default;
  void RenderHotBar();
  void SetSelectedSlot(int slot) { selected_slot_ = slot; }

 private:
  Sprite* hotbar_;
  Sprite* hotbar_select_tile_;
  Sprite* hotbar_select_border_;
  int selected_slot_{0};
};