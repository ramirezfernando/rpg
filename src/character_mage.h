#include "character.h"

#ifndef CHARACTER_MAGE_H
#define CHARACTER_MAGE_H

class Mage : public Character {
 public:
  Mage(const char* folder_path, int x_pos, int y_pos);
  void SetFolderPathFromDirection(std::string direction) override;
};

#endif