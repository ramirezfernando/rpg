#pragma once

namespace Math {

// Calculates the 1D index from a 2D matrix's row and column (both zero-based).
int GetRowMajorOrderIndex(int row, int column);

// Normalizes coordinates on the screen to tile map's row and column.
int GetRowMajorOrderIndexFromCoordinates(int x, int y);

}  // namespace Math