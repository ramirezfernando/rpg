#include "util.h"

SDL_Texture* Util::LoadTexture(const char* file_name) {
  SDL_Surface* tmp_surface = IMG_Load(file_name);
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(Game::renderer_, tmp_surface);
  SDL_FreeSurface(tmp_surface);
  return texture;
}

int Util::GetTileIndex(int col, int row, int tileset_columns) {
  return row * tileset_columns + col;
}