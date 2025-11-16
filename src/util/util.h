#pragma once

#include "game.h"

namespace Util {

SDL_Texture* LoadTexture(const char* file_name);
int GetTileIndex(int col, int row, int tileset_columns = 4);

}  // namespace Util