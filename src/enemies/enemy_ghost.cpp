#include "enemy_ghost.h"

Ghost::Ghost(int x_pos, int y_pos) {
  // Initialize the ghost facing down (facing the user)
  folder_path_ = Constants::ENEMY_GHOST_DOWN_FOLDER_PATH;
  // The ghost has 3 images for each direction
  frames_ = 3;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  health_ = 100;
}