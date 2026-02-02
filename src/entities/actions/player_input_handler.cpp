#include "player_input_handler.h"

#include <cmath>
#include <optional>

#include "constants/entity_constants.h"
#include "entities/entity.h"
#include "ui/hud.h"
#include "util/logger.h"
#include "util/movement.h"
#include "world/map.h"

bool InputHandler::HandleInput(Entity& player, Map& map, HUD& hud) {
  int dx = 0;
  int dy = 0;
  bool is_running = false;
  Direction facing_direction = Direction::Down;

  // Get input from keyboard.
  GetMovementInput(dx, dy, is_running, facing_direction);
  GetHudInput(hud);

  // No input: return to idle.
  if (!Movement::IsMoving(dx, dy)) {
    player.SetPathForAction(Action::Idle);
    player.IncrementAnimationFrameIndexAfterInterval();
    return false;
  }

  player.SetDirectionFacing(facing_direction);

  // Normalize diagonal movement.
  if (Movement::IsMovingDiagonally(dx, dy)) {
    int base_gap = Constants::ENTITY_WALK_GAP;
    int gap = is_running ? base_gap * 2 : base_gap;
    Movement::NormalizeDiagonalMovement(dx, dy, gap);
  }

  // Apply movement.
  Action action = is_running ? Action::Run : Action::Walk;
  return Movement::ApplyMovement(player, dx, dy, map, action);
}

void InputHandler::GetMovementInput(int& dx, int& dy, bool& is_running,
                                    Direction& facing_direction) {
  const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
  int base_gap = Constants::ENTITY_WALK_GAP;
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

void InputHandler::GetHudInput(HUD& hud) {
  const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);

  for (int i = 0; i < 8; ++i) {
    if (keyboard_state[SDL_SCANCODE_1 + i]) {
      hud.SetSelectedSlot(i);
      Logger::Debug("InputHandler",
                    "Hotbar slot " + std::to_string(i + 1) + " selected");
      break;
    }
  }
}
