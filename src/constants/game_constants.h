#pragma once

#include <SDL3/SDL.h>

// Number of nanoseconds in a second.
constexpr int NANOSECONDS_PER_SECOND = 1000000000;
// Frames per second.
constexpr int FRAME_RATE = 30;

namespace Constants {

// Delay between frames in milliseconds.
inline constexpr const Uint64 FRAME_DELAY = NANOSECONDS_PER_SECOND / FRAME_RATE;

// The size of the SDL3 window.
inline constexpr const int WINDOW_SIZE = 768;

}  // namespace Constants