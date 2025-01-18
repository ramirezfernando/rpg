#include "character_mage.h"

Mage::Mage(const char* file_path, int x_pos, int y_pos) {
  file_path_ = file_path;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  frames_ = 3;
  delay_ = 70;
  count_ = 0;
}