#include "util.h"

#include "core/game.h"
#include "graphics/renderer.h"

SDL_Texture* Util::LoadTexture(const char* file_name) {
  SDL_Surface* tmp_surface = IMG_Load(file_name);
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(Renderer::renderer_, tmp_surface);
  SDL_FreeSurface(tmp_surface);
  return texture;
}

int Util::GetRowMajorOrderIndex(int row, int column) {
  return row * Constants::MAP_COLUMNS + column;
}

int Util::GetRowMajorOrderIndexFromCoordinates(int x, int y) {
  // Normalizes coordinates on the screen to tile map rows and columns.
  int row = y / (Constants::SPRITE_HEIGHT * Constants::SPRITE_SCALE) + 1;
  int column = x / (Constants::SPRITE_WIDTH * Constants::SPRITE_SCALE) + 1;
  return GetRowMajorOrderIndex(row, column);
}