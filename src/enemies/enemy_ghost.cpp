#include "enemy_ghost.h"

Ghost::Ghost(int x_pos, int y_pos) {
  folder_path_ = Constants::ENEMY_GHOST_DOWN_FOLDER_PATH;
  frames_ = 3;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
}