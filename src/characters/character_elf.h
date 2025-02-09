#pragma once

#include "character.h"

class Elf : public Character {
 public:
  Elf(int x_pos, int y_pos);
  void SetFolderPathFromDirection(Constants::Direction direction) override;
};