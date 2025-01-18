#include "game.h"

#ifndef UTIL_H
#define UTIL_H

namespace Util {

SDL_Texture* LoadTexture(const char* file_name);
void RenderInvertedTexture(SDL_Texture* texture, SDL_Rect src_rect,
                           SDL_Rect dest_rect, SDL_RendererFlip flip);

}  // namespace Util

#endif