#include "player_input_handler.h"

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

#include <cstddef>
#include <ranges>
#include <span>
#include <string>

#include "constants/entity_constants.h"
#include "entities/entity.h"
#include "graphics/sprite.h"
#include "ui/hud.h"
#include "util/logger.h"
#include "util/movement.h"

bool InputHandler::HandleInput(Entity& player, HUD& hud) {

  Sprite::Coordinate coordinate{.x_pos = 0, .y_pos = 0};
  bool is_running = false;
  Direction facing_direction = Direction::Down;

  // Get input from keyboard.
  GetMovementInput(coordinate, is_running, facing_direction);
  GetHudInput(hud);

  // No input: return to idle.
  if (!Movement::IsMoving(coordinate)) {
    player.SetPathForAction(Action::Idle);
    player.IncrementAnimationFrameIndexAfterInterval();
    return false;
  }

  player.SetDirectionFacing(facing_direction);

  // Normalize diagonal movement.
  if (Movement::IsMovingDiagonally(coordinate)) {
    const int base_gap = Constants::ENTITY_WALK_GAP;
    const int gap = is_running ? base_gap * 2 : base_gap;
    Movement::NormalizeDiagonalMovement(coordinate, gap);
  }

  // Apply movement.
  const Action action = is_running ? Action::Run : Action::Walk;
  return Movement::ApplyMovement(player, coordinate, action);
}

std::span<const bool> InputHandler::GetKeyboardState() {
  int num_keys = 0;
  const bool* raw_keyboard_state = SDL_GetKeyboardState(&num_keys);
  // Wrap the raw pointer in a span to make it "bounds-aware" and safer to use.
  return {raw_keyboard_state, static_cast<size_t>(num_keys)};
}

void InputHandler::GetMovementInput(Sprite::Coordinate& coordinate,
                                    bool& is_running,
                                    Direction& facing_direction) {
  const int base_gap = Constants::ENTITY_WALK_GAP;
  int gap = base_gap;
  auto keyboard_state = GetKeyboardState();

  // Check for running modifier.
  if (keyboard_state[SDL_SCANCODE_LSHIFT] ||
      keyboard_state[SDL_SCANCODE_RSHIFT]) {
    gap = base_gap * 2;
    is_running = true;
  }

  // Vertical movement.
  if (keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S]) {
    coordinate.y_pos -= gap;
    facing_direction = Direction::Up;
  } else if (keyboard_state[SDL_SCANCODE_S] &&
             !keyboard_state[SDL_SCANCODE_W]) {
    coordinate.y_pos += gap;
    facing_direction = Direction::Down;
  }

  // Horizontal movement.
  if (keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D]) {
    coordinate.x_pos -= gap;
    facing_direction = Direction::Left;
  } else if (keyboard_state[SDL_SCANCODE_D] &&
             !keyboard_state[SDL_SCANCODE_A]) {
    coordinate.x_pos += gap;
    facing_direction = Direction::Right;
  }
}

void InputHandler::GetHudInput(HUD& hud) {
  auto keyboard_state = GetKeyboardState();
  const int hud_slots = 8;
  for (const int i : std::ranges::iota_view{0, hud_slots}) {
    if (keyboard_state[SDL_SCANCODE_1 + static_cast<size_t>(i)]) {
      hud.SetSelectedSlot(i);
      Logger::Debug("InputHandler",
                    "Hotbar slot " + std::to_string(i + 1) + " selected");
      break;
    }
  }
}
