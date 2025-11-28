#include "game.h"

#include <cmath>
#include <iostream>

#include "characters/character.h"
#include "characters/fern.h"
#include "constants/constants.h"
#include "map/map_renderer.h"

SDL_Renderer* Game::renderer_ = nullptr;
SDL_Event Game::event_;

namespace {

bool IsMoving(int dx, int dy) {
  return dx != 0 || dy != 0;
}

bool IsMovingDiagonally(int dx, int dy) {
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
  map_renderer_ = std::unique_ptr<MapRenderer>(new MapRenderer());
  if (map_renderer_) {
#if defined(DEBUG_MODE)
    std::cout << "Map renderer created" << std::endl;
#endif  // DEBUG_MODE
  }
}

void Game::Render() {
  SDL_RenderClear(renderer_);
  // Order of rendering matters: first rendered = back, last rendered = front.
  map_renderer_->RenderGrassTiles();
  map_renderer_->RenderGrassWater();
  map_renderer_->RenderWoodFence();
  map_renderer_->RenderTinyHouse();
  map_renderer_->RenderWaterfall();
  map_renderer_->RenderCliff();
  player_->Render();
  SDL_RenderPresent(renderer_);  // Double buffering
}

void Game::HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
      is_running_ = false;
    }
  }

  // Continuous keyboard state for multi-key handling.
  const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
  int base_gap = Constants::CHARACTER_WALK_GAP;
  int gap = base_gap;
  bool is_character_running = false;
  if (keyboard_state[SDL_SCANCODE_LSHIFT] ||
      keyboard_state[SDL_SCANCODE_RSHIFT]) {
    gap = base_gap * 2;
    is_character_running = true;
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

  if (!IsMoving(dx, dy)) {
    player_->SetPathForAction(Action::Idle);
    return;
  }

  if (IsMovingDiagonally(dx, dy)) {
    NormalizeDiagonalMovement(dx, dy, gap);
  }
  player_->SetXPos(player_->GetXPos() + dx);
  player_->SetYPos(player_->GetYPos() + dy);
  player_->SetPathForAction(is_character_running ? Action::Run : Action::Walk);
  player_->IncrementAnimationFrameIndex();
}