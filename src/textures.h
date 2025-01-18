#include "game.h"

#ifndef TEXTURES_H
#define TEXTURES_H
class Textures {
 public:
  static SDL_Texture* LoadTexture(const char* file_name);
  static void RenderInvertedTexture(SDL_Texture* texture, SDL_Rect src_rect,
                                    SDL_Rect dest_rect, SDL_RendererFlip flip);
};

#endif