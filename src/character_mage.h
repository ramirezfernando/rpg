#pragma once

#include "character.h"

class Mage : public Character {
 public:
  Mage(const char* folder_path, int x_pos, int y_pos);
  void SetFolderPathFromDirection(Constants::Direction direction) override;
};