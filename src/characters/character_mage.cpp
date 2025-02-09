#include "character_mage.h"

Mage::Mage(int x_pos, int y_pos) {
  // Initialize the mage facing down (facing the user)
  folder_path_ = Constants::CHARACTER_MAGE_DOWN_FOLDER_PATH;
  // The mage has 3 images for each direction
  frames_ = 3;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
}

void Mage::SetFolderPathFromDirection(Constants::Direction direction) {
  switch (direction) {
    case Constants::Direction::UP:
      folder_path_ = Constants::CHARACTER_MAGE_UP_FOLDER_PATH;
      break;
    case Constants::Direction::DOWN:
      folder_path_ = Constants::CHARACTER_MAGE_DOWN_FOLDER_PATH;
      break;
    case Constants::Direction::LEFT:
      folder_path_ = Constants::CHARACTER_MAGE_LEFT_FOLDER_PATH;
      break;
    case Constants::Direction::RIGHT:
      folder_path_ = Constants::CHARACTER_MAGE_RIGHT_FOLDER_PATH;
      break;
  }
}