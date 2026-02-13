#include "hud.h"

#include "cache/cache.h"
#include "constants/game_constants.h"
#include "constants/hud_constants.h"
#include "graphics/sprite.h"

HUD::HUD() {
  Cache* cache = Cache::GetInstance();
  hotbar_ = cache->GetOrCreateSpriteSheet(
      "assets/sprites/hud/inventory/hotbar.png",
      Sprite::Dimension{.width = Constants::HOTBAR_WIDTH,
                        .height = Constants::HOTBAR_HEIGHT});
  hotbar_select_tile_ = cache->GetOrCreateSpriteSheet(
      "assets/sprites/hud/inventory/hotbar_select_tile.png",
      Sprite::Dimension{.width = Constants::SELECT_TILE_WIDTH,
                        .height = Constants::SELECT_TILE_HEIGHT});
  hotbar_select_border_ = cache->GetOrCreateSpriteSheet(
      "assets/sprites/hud/inventory/hotbar_select_border.png",
      Sprite::Dimension{.width = Constants::SELECT_TILE_WIDTH,
                        .height = Constants::SELECT_TILE_HEIGHT});
}

void HUD::RenderHotBar() {
  if (hotbar_ != nullptr && hotbar_select_tile_ != nullptr &&
      hotbar_select_border_ != nullptr) {
    const int HOTBAR_X_POSITION =
        Constants::WINDOW_SIZE - Constants::HOTBAR_POS_X_OFFSET;
    const int HOTBAR_Y_POSITION =
        Constants::WINDOW_SIZE - Constants::HOTBAR_POS_Y_OFFSET;
    hotbar_->RenderSprite(0, Sprite::Coordinate{.x_pos = HOTBAR_X_POSITION,
                                                .y_pos = HOTBAR_Y_POSITION});

    // Render selection tile and border around selected slot.
    const int slot_x = (HOTBAR_X_POSITION + Constants::SELECTED_SLOT_X_OFFSET +
                        (selected_slot_ * Constants::SELECTED_SLOT_GAP));
    const int slot_y = HOTBAR_Y_POSITION + Constants::SELECTED_SLOT_Y_OFFSET;
    hotbar_select_tile_->RenderSprite(
        Constants::SELECTED_SLOT_DEFAULT,
        Sprite::Coordinate{.x_pos = slot_x, .y_pos = slot_y});
    hotbar_select_border_->RenderSprite(
        Constants::SELECTED_SLOT_DEFAULT,
        Sprite::Coordinate{.x_pos = slot_x, .y_pos = slot_y});
  }
}