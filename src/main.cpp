#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <memory>

#include "constants/game_constants.h"
#include "core/game.h"

int main() {
  Uint32 frame_start{};
  Uint32 frame_time{};
  auto game = std::make_unique<Game>();

  while (game->IsRunning()) {
    frame_start = SDL_GetTicks();
    game->Render();
    game->Update();

    // Handle frame rate.
    frame_time = SDL_GetTicks() - frame_start;
    if (Constants::FRAME_DELAY > frame_time) {
      SDL_Delay(Constants::FRAME_DELAY - frame_time);
    }
  }

  return 0;
}