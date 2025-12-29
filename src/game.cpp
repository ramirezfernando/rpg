#include "game.h"

#include <cmath>
#include <iostream>
#include <optional>

#include "characters/character.h"
#include "characters/fern.h"
#include "characters/kat.h"
#include "constants/constants.h"
#include "map/map.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

namespace {

static bool IsPlayerMoving(int dx, int dy) {
  return dx != 0 || dy != 0;
}

static bool IsPlayerMovingDiagonally(int dx, int dy) {
  return dx != 0 && dy != 0;
}

// Prevent faster diagonal movement using Pythagorean theorem. We want the
// hypotenuse to equal `gap`, e.g., `gap = sqrt(dx^2 + dy^2)`.
static void NormalizeDiagonalMovement(int& dx, int& dy, int gap) {
  double hypotenuse =
      std::hypot(static_cast<double>(dx), static_cast<double>(dy));
  double factor = static_cast<double>(gap) / hypotenuse;
  dx = static_cast<int>(std::round(dx * factor));
  dy = static_cast<int>(std::round(dy * factor));
}

static bool IsPlayerBehindFence(int x, int y) {
  return (y >= 400 && y <= 440) || (y >= 260 && y <= 300 && x <= 260);
}

static bool IsPlayerBehindHouse(int x, int y) {
  return y <= 200 && x <= 670;
}

static bool ShouldRenderPlayerFirst(int x, int y) {
  return IsPlayerBehindFence(x, y) || IsPlayerBehindHouse(x, y);
}

}  // namespace

Game::~Game() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
  IMG_Quit();
#if defined(DEBUG_MODE)
  std::cout << "Game destroyed" << std::endl;
#endif  // DEBUG_MODE
}

void Game::Init(const char* title, int x_pos, int y_pos, int width,
                int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, 0);
    if (window_) {
#if defined(DEBUG_MODE)
      std::cout << "Window created" << std::endl;
#endif  // DEBUG_MODE
    }
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_) {
      SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
#if defined(DEBUG_MODE)
      std::cout << "Renderer created" << std::endl;
#endif  // DEBUG_MODE
    }
    is_running_ = true;
  } else {
    is_running_ = false;
  }

  player_ = std::unique_ptr<Character>(new Fern());
  if (player_) {
#if defined(DEBUG_MODE)
    std::cout << "Character created" << std::endl;
#endif  // DEBUG_MODE
  }
  npc_ = std::unique_ptr<Character>(new Kat());
  if (npc_) {
#if defined(DEBUG_MODE)
    std::cout << "Character created" << std::endl;
#endif  // DEBUG_MODE
  }
  map_ = std::unique_ptr<Map>(new Map());
  if (map_) {
#if defined(DEBUG_MODE)
    std::cout << "Map renderer created" << std::endl;
#endif  // DEBUG_MODE
  }
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  // Order of rendering matters: first rendered = back, last rendered = front.
  map_->RenderGrassDirt();
  map_->RenderGrassWater();
  map_->RenderWaterfall();
  map_->RenderCliff();

  if (ShouldRenderPlayerFirst(player_->GetXPos(), player_->GetYPos())) {
    player_->Render();
    map_->RenderWoodFence();
    map_->RenderHouse();
  } else {
    map_->RenderWoodFence();
    map_->RenderHouse();
    player_->Render();
  }

  npc_->Render();

  SDL_RenderPresent(renderer_);  // Double buffering
}

void Game::HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      is_running_ = false;
    }
  }

  // Continuous keyboard state for multi-key handling.
  const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
  int base_gap = Constants::CHARACTER_WALK_GAP;
  int gap = base_gap;
  bool is_player_running = false;
  if (keyboard_state[SDL_SCANCODE_LSHIFT] ||
      keyboard_state[SDL_SCANCODE_RSHIFT]) {
    gap = base_gap * 2;
    is_player_running = true;
  }

  int dx = 0;
  int dy = 0;

  // Vertical movement.
  if (keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S]) {
    dy -= gap;
    player_->SetDirectionFacing(Direction::Up);
  } else if (keyboard_state[SDL_SCANCODE_S] &&
             !keyboard_state[SDL_SCANCODE_W]) {
    dy += gap;
    player_->SetDirectionFacing(Direction::Down);
  }

  // Horizontal movement.
  if (keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D]) {
    dx -= gap;
    player_->SetDirectionFacing(Direction::Left);
  } else if (keyboard_state[SDL_SCANCODE_D] &&
             !keyboard_state[SDL_SCANCODE_A]) {
    dx += gap;
    player_->SetDirectionFacing(Direction::Right);
  }

  if (!IsPlayerMoving(dx, dy)) {
    player_->SetPathForAction(Action::Idle);
    return;
  }

  if (IsPlayerMovingDiagonally(dx, dy)) {
    NormalizeDiagonalMovement(dx, dy, gap);
  }
  // Check for collision before updating position.
  int new_x = player_->GetXPos() + dx;
  int new_y = player_->GetYPos() + dy;
  std::optional<int> tile = map_->GetTopmostTile(new_x, new_y);
  if (tile.has_value()) {
#if defined(DEBUG_MODE)
    std::cout << "Tile: " << tile.value() << std::endl;
#endif  // DEBUG_MODE

    if (map_->IsCollisionTile(tile.value())) {
      // Collision detected; do not move.
      player_->SetPathForAction(Action::Idle);
      return;
    }
  } else {
    // Treat empty tiles as collisions.
    player_->SetPathForAction(Action::Idle);
    return;
  }

  if (map_->IsOutOfBounds(new_x, new_y)) {
    player_->SetPathForAction(Action::Idle);
    return;
  }

  player_->SetXPos(new_x);
  player_->SetYPos(new_y);
  player_->SetPathForAction(is_player_running ? Action::Run : Action::Walk);
  player_->IncrementAnimationFrameIndex();
}
