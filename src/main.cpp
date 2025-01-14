#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "game.h"

using namespace std;

int main(int argc, const char * argv[]) {
  constexpr int FPS = 30;
  constexpr int FRAME_DELAY = 1000 / FPS;
  Uint32 frame_start;
  int frame_time;

  Game *game = nullptr;
  game = new Game();

  // Create the window
  game->Init("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

  // Game loop
  while (game->GetIsRunning()) {
    frame_start = SDL_GetTicks();
    game->HandleEvents();
    game->Update();
    game->Render();

    // Handles frame rate
    frame_time = SDL_GetTicks() - frame_start;
    if (FRAME_DELAY > frame_time) {
      SDL_Delay(FRAME_DELAY - frame_time);
    }
  }
  game->Clean();
  return 0;
}