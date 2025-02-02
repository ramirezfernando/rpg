#include "character.h"

class Mage : public Character {
 public:
  Mage(const char* file_path, int x_pos, int y_pos);
  void Attack();
};