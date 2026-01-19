#include "hud.h"

#include "resource/resource_manager.h"
#include "util/constants.h"

HUD::HUD() {
  ResourceManager& rm = ResourceManager::GetInstance();
  inventory_ = rm.GetSpriteSheet("assets/sprites/hud/inventory.png", 180, 48);
}

void HUD::RenderInventory() {
  if (inventory_) {
    inventory_->RenderSprite(0, /*dst_x=*/Constants::WINDOW_SIZE / 7,
                             /*dst_y=*/Constants::WINDOW_SIZE - 110);
  }
}