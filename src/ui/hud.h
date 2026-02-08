#pragma once

#include "graphics/sprite.h"

class HUD {
 public:
  HUD();
  ~HUD() = default;
  void RenderHotBar();
  void SetSelectedSlot(int slot) { selected_slot_ = slot; }

 private:
  Sprite* hotbar_{nullptr};
  Sprite* hotbar_select_tile_{nullptr};
  Sprite* hotbar_select_border_{nullptr};
  int selected_slot_{0};
};