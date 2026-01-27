#include "game_constants.h"

// Number of milliseconds in a second.
constexpr int MILISECONDS_PER_SECOND = 1000;
// Frames per second.
constexpr int FRAME_RATE = 30;

namespace Constants {

const Uint32 FRAME_DELAY = MILISECONDS_PER_SECOND / FRAME_RATE;

const int WINDOW_SIZE = 768;

}  // namespace Constants