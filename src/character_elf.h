#include "character.h"

#ifndef CHARACTER_ELF_H
#define CHARACTER_ELF_H

class Elf : public Character {
 public:
  Elf(const char* folder_path, int x_pos, int y_pos);
  void SetFolderPathFromDirection(Constants::Direction direction) override;
};

#endif