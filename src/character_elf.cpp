#include "character_elf.h"

Elf::Elf(const char* folder_path, int x_pos, int y_pos) {
  folder_path_ = folder_path;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  frames_ = 3;
  delay_ = 70;
  count_ = 0;
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