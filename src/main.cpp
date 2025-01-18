#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "constants/game_constants.h"
#include "game.h"

int main(int argc, const char* argv[]) {
  Uint32 frame_start;
  int frame_time;
  std::unique_ptr<Game> game(new Game());

  // Create the window
  game->Init("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 736, 736);

  // Game loop
  while (game->GetIsRunning()) {
    frame_start = SDL_GetTicks();
    game->Update();
    game->Render();
    game->HandleEvents();

    // Handles frame rate
    frame_time = SDL_GetTicks() - frame_start;
    if (Constants::FRAME_DELAY > frame_time) {
      SDL_Delay(Constants::FRAME_DELAY - frame_time);
    }
  }
  game->Clean();
  return 0;
}