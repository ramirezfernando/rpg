#pragma once

#include <SDL2/SDL.h>

namespace Util {

SDL_Texture* LoadTexture(const char* file_name);

// Calculates the 1D index from a 2D matrix's row and column (both zero-based).
int GetRowMajorOrderIndex(int row, int column);

// Normalizes coordinates on the screen to tile map's row and column.
int GetRowMajorOrderIndexFromCoordinates(int x, int y);

}  // namespace Util