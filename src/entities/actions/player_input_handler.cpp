#include "player_input_handler.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>

#include <cstddef>
#include <ranges>
#include <span>
#include <string>

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
    const int base_gap = Constants::ENTITY_WALK_GAP;
    const int gap = is_running ? base_gap * 2 : base_gap;
    Movement::NormalizeDiagonalMovement(dx, dy, gap);
  }

  // Apply movement.
  const Action action = is_running ? Action::Run : Action::Walk;
  return Movement::ApplyMovement(player, dx, dy, map, action);
}

std::span<const Uint8> InputHandler::GetKeyboardState() {
  int num_keys = 0;
  const Uint8* raw_keyboard_state = SDL_GetKeyboardState(&num_keys);
  // Wrap the raw pointer in a span to make it "bounds-aware" and safer to use.
  return {raw_keyboard_state, static_cast<size_t>(num_keys)};
}

void InputHandler::GetMovementInput(int& dx, int& dy, bool& is_running,
                                    Direction& facing_direction) {
  const int base_gap = Constants::ENTITY_WALK_GAP;
  int gap = base_gap;
  auto keyboard_state = GetKeyboardState();

  // Check for running modifier.
  if (keyboard_state[SDL_SCANCODE_LSHIFT] != 0u ||
      keyboard_state[SDL_SCANCODE_RSHIFT] != 0u) {
    gap = base_gap * 2;
    is_running = true;
  }

  // Vertical movement.
  if (keyboard_state[SDL_SCANCODE_W] != 0u &&
      keyboard_state[SDL_SCANCODE_S] == 0u) {
    dy -= gap;
    facing_direction = Direction::Up;
  } else if (keyboard_state[SDL_SCANCODE_S] != 0u &&
             keyboard_state[SDL_SCANCODE_W] == 0u) {
    dy += gap;
    facing_direction = Direction::Down;
  }

  // Horizontal movement.
  if (keyboard_state[SDL_SCANCODE_A] != 0u &&
      keyboard_state[SDL_SCANCODE_D] == 0u) {
    dx -= gap;
    facing_direction = Direction::Left;
  } else if (keyboard_state[SDL_SCANCODE_D] != 0u &&
             keyboard_state[SDL_SCANCODE_A] == 0u) {
    dx += gap;
    facing_direction = Direction::Right;
  }
}

void InputHandler::GetHudInput(HUD& hud) {
  auto keyboard_state = GetKeyboardState();
  const int hud_slots = 8;
  for (const int i : std::ranges::iota_view{0, hud_slots}) {
    if (keyboard_state[static_cast<size_t>(SDL_SCANCODE_1 + i)] != 0u) {
      hud.SetSelectedSlot(i);
      Logger::Debug("InputHandler",
                    "Hotbar slot " + std::to_string(i + 1) + " selected");
      break;
    }
  }
}
