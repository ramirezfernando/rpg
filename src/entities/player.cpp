#include "player.h"

#include <iostream>

#include "cache/cache.h"
#include "graphics/sprite.h"
#include "util/constants.h"

Player::Player()
    : Entity(Cache::GetInstance()->GetOrCreateSpriteSheet(
          /*path=*/"assets/sprites/characters/fern/idle.png",
          /*sprite_w=*/32, /*sprite_h=*/32)) {
  sprite_sheet_columns_ = renderer()->GetColumns();
}

int Player::GetInitialAnimationFrame(Action action, Direction direction) const {
  switch (action) {
    // 3x4
    case Action::Idle:
      switch (direction) {
        case Direction::Up:
          return 4;
        case Direction::Down:
          return 0;
        case Direction::Left:
        case Direction::Right:
          return 8;
      }
      break;
    // 3x6
    case Action::Walk:
      switch (direction) {
        case Direction::Up:
          return 6;
        case Direction::Down:
          return 0;
        case Direction::Left:
        case Direction::Right:
          return 12;
      }
      break;
    // 3x8
    case Action::Run:
      switch (direction) {
        case Direction::Up:
          return 8;
        case Direction::Down:
          return 0;
        case Direction::Left:
        case Direction::Right:
          return 16;
      }
      break;
  }
}

int Player::GetSpriteSheetColumns() const {
  return sprite_sheet_columns_;
}

void Player::SetPathForAction(Action action) {
  // Only load new sprite sheet if action has changed.
  if (GetCurrentAction() == action) {
    return;
  }

  const char* action_path = nullptr;
  switch (action) {
    case Action::Idle:
      action_path = "assets/sprites/characters/fern/idle.png";
      break;
    case Action::Walk:
      action_path = "assets/sprites/characters/fern/walk.png";
      break;
    case Action::Run:
      action_path = "assets/sprites/characters/fern/run.png";
      break;
  }

  SetAction(action);
  // Use the Cache to load/cache the sprite sheet.
  Sprite* new_renderer = Cache::GetInstance()->GetOrCreateSpriteSheet(
      action_path, /*sprite_w=*/32, /*sprite_h=*/32);
  if (new_renderer) {
    SetRenderer(new_renderer);
  }
}