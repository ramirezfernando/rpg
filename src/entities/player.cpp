#include "player.h"

#include "cache/cache.h"
#include "constants/entity_constants.h"
#include "entities/entity.h"
#include "graphics/sprite.h"

Player::Player()
    : Entity(Cache::GetInstance()->GetOrCreateSpriteSheet(
          /*file_path=*/"assets/sprites/entities/fern/idle.png",
          Sprite::Dimension{.width = Constants::FERN_SPRITE_WIDTH,
                            .height = Constants::FERN_SPRITE_HEIGHT})),
      sprite_sheet_columns_{sprite()->GetColumns()} {}

int Player::GetInitialAnimationFrame(Action action, Direction direction) const {
  switch (action) {
    // 3x4
    case Action::Idle:
      switch (direction) {
        case Direction::Up:
          return Constants::IDLE_UP_INITIAL_FRAME;
        case Direction::Down:
          return Constants::IDLE_DOWN_INITIAL_FRAME;
        case Direction::Left:
        case Direction::Right:
          return Constants::IDLE_LEFT_AND_RIGHT_INITIAL_FRAME;
      }
      break;
    // 3x6
    case Action::Walk:
      switch (direction) {
        case Direction::Up:
          return Constants::WALK_UP_INITIAL_FRAME;
        case Direction::Down:
          return Constants::WALK_DOWN_INITIAL_FRAME;
        case Direction::Left:
        case Direction::Right:
          return Constants::WALK_LEFT_AND_RIGHT_INITIAL_FRAME;
      }
      break;
    // 3x8
    case Action::Run:
      switch (direction) {
        case Direction::Up:
          return Constants::RUN_UP_INITIAL_FRAME;
        case Direction::Down:
          return Constants::RUN_DOWN_INITIAL_FRAME;
        case Direction::Left:
        case Direction::Right:
          return Constants::RUN_LEFT_AND_RIGHT_INITIAL_FRAME;
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
      action_path = "assets/sprites/entities/fern/idle.png";
      break;
    case Action::Walk:
      action_path = "assets/sprites/entities/fern/walk.png";
      break;
    case Action::Run:
      action_path = "assets/sprites/entities/fern/run.png";
      break;
  }

  SetAction(action);
  const Sprite* sprite = Cache::GetInstance()->GetOrCreateSpriteSheet(
      action_path, Sprite::Dimension{.width = Constants::FERN_SPRITE_WIDTH,
                                     .height = Constants::FERN_SPRITE_HEIGHT});
  if (sprite != nullptr) {
    SetSprite(sprite);
  }
}