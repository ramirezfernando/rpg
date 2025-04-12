#pragma once

#include <vector>
#include "constants/asset_constants.h"
#include "enemies/enemy.h"
#include "game.h"

class Spawner {
 public:
  Spawner();
  ~Spawner();
  void Update(int character_x_pos, int character_y_pos);
  void Render();
  void AddEnemy(Enemy* enemy);
  void RemoveEnemy(Enemy* enemy);

 private:
  std::vector<Enemy*> enemies_;
};