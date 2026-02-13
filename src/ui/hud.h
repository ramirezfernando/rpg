#pragma once

#include "graphics/sprite.h"

class HUD {
 public:
  HUD();
  ~HUD() = default;
  HUD(const HUD&) = delete;
  HUD& operator=(const HUD&) = delete;
  HUD(HUD&&) = delete;
  HUD& operator=(HUD&&) = delete;

  void RenderHotBar();
  void SetSelectedSlot(int slot) { selected_slot_ = slot; }

 private:
  const Sprite* hotbar_{nullptr};
  const Sprite* hotbar_select_tile_{nullptr};
  const Sprite* hotbar_select_border_{nullptr};
  int selected_slot_{0};
};