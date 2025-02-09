#include "character_elf.h"

Elf::Elf(int x_pos, int y_pos) {
  // Initialize the elf facing down (facing the user)
  folder_path_ = Constants::CHARACTER_ELF_DOWN_FOLDER_PATH;
  // The elf has 3 images for each direction
  frames_ = 3;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
}

void Elf::SetFolderPathFromDirection(Constants::Direction direction) {
  switch (direction) {
    case Constants::Direction::UP:
      folder_path_ = Constants::CHARACTER_ELF_UP_FOLDER_PATH;
      break;
    case Constants::Direction::DOWN:
      folder_path_ = Constants::CHARACTER_ELF_DOWN_FOLDER_PATH;
      break;
    case Constants::Direction::LEFT:
      folder_path_ = Constants::CHARACTER_ELF_LEFT_FOLDER_PATH;
      break;
    case Constants::Direction::RIGHT:
      folder_path_ = Constants::CHARACTER_ELF_RIGHT_FOLDER_PATH;
      break;
  }
}