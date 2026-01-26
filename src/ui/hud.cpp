#include "hud.h"

#include "cache/cache.h"
#include "util/constants.h"

HUD::HUD() {
  Cache* cache = Cache::GetInstance();
  hotbar_ = cache->GetOrCreateSpriteSheet(
      "assets/sprites/hud/inventory/hotbar.png", 165, 28);
  hotbar_select_tile_ = cache->GetOrCreateSpriteSheet(
      "assets/sprites/hud/inventory/hotbar_select_tile.png", 18, 18);
  hotbar_select_border_ = cache->GetOrCreateSpriteSheet(
      "assets/sprites/hud/inventory/hotbar_select_border.png", 18, 18);
  selected_slot_ = 0;
}

void HUD::RenderHotBar() {
  if (hotbar_ && hotbar_select_tile_ && hotbar_select_border_) {
    hotbar_->RenderSprite(0, /*dst_x=*/Constants::WINDOW_SIZE - 632,
                          /*dst_y=*/Constants::WINDOW_SIZE - 84);
    // Render selection tile and border around selected slot.
    int slot_x = (Constants::WINDOW_SIZE - 632 + 8 + selected_slot_ * 57) + 10;
    int slot_y = (Constants::WINDOW_SIZE - 84 + 8) + 8;
    hotbar_select_tile_->RenderSprite(0, /*dst_x=*/slot_x, /*dst_y=*/slot_y);
    hotbar_select_border_->RenderSprite(0, /*dst_x=*/slot_x, /*dst_y=*/slot_y);
  }
}