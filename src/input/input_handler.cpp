#include "input_handler.h"

#include <cmath>
#include <optional>

#include "characters/character.h"
#include "constants/constants.h"
#include "map/map.h"
#include "util/logger.h"

bool IsPlayerMoving(int dx, int dy) {
  return dx != 0 || dy != 0;
}

bool IsPlayerMovingDiagonally(int dx, int dy) {
  return dx != 0 && dy != 0;
}

// Normalize diagonal movement to prevent faster diagonal movement.
void NormalizeDiagonalMovement(int& dx, int& dy, int gap) {
  double hypotenuse =
      std::hypot(static_cast<double>(dx), static_cast<double>(dy));
  double factor = static_cast<double>(gap) / hypotenuse;
  dx = static_cast<int>(std::round(dx * factor));
  dy = static_cast<int>(std::round(dy * factor));
}

bool InputHandler::HandleInput(Character* player, Map* map) {
  if (!player || !map) {
    Logger::Error("InputHandler", "Player or map is null");
    return false;
  }

  int dx = 0;
  int dy = 0;
  bool is_running = false;
  Direction facing_direction = Direction::Down;

  // Get movement input from keyboard.
  GetMovementInput(dx, dy, is_running, facing_direction);
  player->SetDirectionFacing(facing_direction);

  // No input: return to idle.
  if (!IsPlayerMoving(dx, dy)) {
    player->SetPathForAction(Action::Idle);
    return false;
  }

  // Normalize diagonal movement.
  if (IsPlayerMovingDiagonally(dx, dy)) {
    int base_gap = Constants::CHARACTER_WALK_GAP;
    int gap = is_running ? base_gap * 2 : base_gap;
    NormalizeDiagonalMovement(dx, dy, gap);
  }

  // Calculate new position.
  int new_x = player->GetXPos() + dx;
  int new_y = player->GetYPos() + dy;

  // Validate movement.
  if (!IsMovementValid(new_x, new_y, map)) {
    player->SetPathForAction(Action::Idle);
    return false;
  }

  // Apply movement.
  player->SetXPos(new_x);
  player->SetYPos(new_y);
  player->SetPathForAction(is_running ? Action::Run : Action::Walk);
  player->IncrementAnimationFrameIndex();

  return true;
}

void InputHandler::GetMovementInput(int& dx, int& dy, bool& is_running,
                                    Direction& facing_direction) {
  const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
  int base_gap = Constants::CHARACTER_WALK_GAP;
  int gap = base_gap;

  // Check for running modifier.
  if (keyboard_state[SDL_SCANCODE_LSHIFT] ||
      keyboard_state[SDL_SCANCODE_RSHIFT]) {
    gap = base_gap * 2;
    is_running = true;
  }

  // Vertical movement.
  if (keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S]) {
    dy -= gap;
    facing_direction = Direction::Up;
  } else if (keyboard_state[SDL_SCANCODE_S] &&
             !keyboard_state[SDL_SCANCODE_W]) {
    dy += gap;
    facing_direction = Direction::Down;
  }

  // Horizontal movement.
  if (keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D]) {
    dx -= gap;
    facing_direction = Direction::Left;
  } else if (keyboard_state[SDL_SCANCODE_D] &&
             !keyboard_state[SDL_SCANCODE_A]) {
    dx += gap;
    facing_direction = Direction::Right;
  }
}

bool InputHandler::IsMovementValid(int x, int y, Map* map) {
  // Check bounds.
  if (map->IsOutOfBounds(x, y)) {
    return false;
  }

  // Check collision.
  std::optional<int> tile = map->GetTopmostTile(x, y);
  if (!tile.has_value() || map->IsCollisionTile(tile.value())) {
    return false;
  }

  return true;
}
