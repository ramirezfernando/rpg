#pragma once

#include <SDL2/SDL.h>

// Number of milliseconds in a second.
constexpr int MILISECONDS_PER_SECOND = 1000;
// Frames per second.
constexpr int FRAME_RATE = 30;

namespace Constants {

// Delay between frames in milliseconds.
inline constexpr const Uint32 FRAME_DELAY = MILISECONDS_PER_SECOND / FRAME_RATE;

// The size of the SDL2 window.
inline constexpr const int WINDOW_SIZE = 768;

}  // namespace Constants