#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "constants/constants.h"
#include "game.h"

int main() {
  std::unique_ptr<Game> game(new Game());
  game->Init("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             Constants::WINDOW_SIZE, Constants::WINDOW_SIZE);

  Uint32 frame_start;
  int frame_time;
  while (game->IsRunning()) {
    frame_start = SDL_GetTicks();
    game->Update();
    game->Render();
    game->HandleEvents();

    // Handle frame rate.
    frame_time = SDL_GetTicks() - frame_start;
    if (Constants::FRAME_DELAY > frame_time) {
      SDL_Delay(Constants::FRAME_DELAY - frame_time);
    }
  }
  return 0;
}