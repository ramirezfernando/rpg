#include "game.h"
#include<unistd.h>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  return;
}
void Game::HandleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
      case SDL_QUIT:
        return;
      case SDL_KEYDOWN:
        return;
    }
    
}
void Game::Update()
{
  return;
}
void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer); // Double buffering
}
void Game::Clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  IMG_Quit();
  cout << "Game cleaned" << endl;
}
bool Game::Running()
{
    return isRunning;
}
void Game::SetRunning(bool _isRunning)
{
    isRunning = _isRunning;
}