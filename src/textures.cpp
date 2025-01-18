#include "textures.h"
#include <string>

SDL_Texture* Textures::LoadTexture(const char* file_name) {
  SDL_Surface* tmp_surface = IMG_Load(file_name);
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(Game::renderer_, tmp_surface);
  SDL_FreeSurface(tmp_surface);
  return texture;
}

void Textures::RenderInvertedTexture(SDL_Texture* texture, SDL_Rect src_rect,
                                     SDL_Rect dest_rect,
                                     SDL_RendererFlip flip) {
  SDL_RenderCopyEx(Game::renderer_, texture, &src_rect, &dest_rect, 0.0, NULL,
                   flip);
}