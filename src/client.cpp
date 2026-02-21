#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

#include <memory>

#include "constants/game_constants.h"
#include "core/game.h"

int main() {
  Uint64 frame_start{};
  Uint64 frame_time{};
  auto game = std::make_unique<Game>();

  while (game->IsRunning()) {
    frame_start = SDL_GetTicks();
    game->Render();
    game->Update();

    // Handle frame rate.
    frame_time = SDL_GetTicks() - frame_start;
    if (Constants::FRAME_DELAY > frame_time) {
      SDL_DelayNS(Constants::FRAME_DELAY - frame_time);
    }
  }

  return 0;
}