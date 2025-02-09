#pragma once

#include "character.h"

class Elf : public Character {
 public:
  Elf(const char* folder_path, int x_pos, int y_pos);
  void SetFolderPathFromDirection(Constants::Direction direction) override;
};