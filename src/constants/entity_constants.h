#pragma once

namespace Constants {

// Speed of idle animation frame changes.
inline constexpr const int ENTITY_IDLE_ANIMATION_SPEED = 6;

// Speed of walk and run animation frame changes.
inline constexpr const int ENTITY_WALK_AND_RUN_ANIMATION_SPEED = 2;

// Gap in pixels for character movement.
inline constexpr const int ENTITY_WALK_GAP = 5;

// The starting X position of the player when the game starts.
inline constexpr const int PLAYER_START_X = 536;

// The starting Y position of the player when the game starts.
inline constexpr const int PLAYER_START_Y = 260;

inline constexpr int ENTITY_SPRITE_WIDTH = 32;
inline constexpr int ENTITY_SPRITE_HEIGHT = 32;
inline constexpr int IDLE_UP_INITIAL_FRAME = 4;
inline constexpr int IDLE_DOWN_INITIAL_FRAME = 0;
inline constexpr int IDLE_LEFT_AND_RIGHT_INITIAL_FRAME = 8;
inline constexpr int WALK_UP_INITIAL_FRAME = 6;
inline constexpr int WALK_DOWN_INITIAL_FRAME = 0;
inline constexpr int WALK_LEFT_AND_RIGHT_INITIAL_FRAME = 12;
inline constexpr int RUN_UP_INITIAL_FRAME = 8;
inline constexpr int RUN_DOWN_INITIAL_FRAME = 0;
inline constexpr int RUN_LEFT_AND_RIGHT_INITIAL_FRAME = 16;
inline constexpr const int DECISION_DURATION = 80;
inline constexpr const int RANDOM_INT_UPPER_BOUND = 99;
inline constexpr const int MOVE_PROBABILITY_PERCENT = 60;

}  // namespace Constants