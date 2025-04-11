#pragma once

#include <vector>
#include "constants/asset_constants.h"
#include "enemies/enemy.h"
#include "game.h"

class Spawner {
 public:
  Spawner();
  ~Spawner();
  void Update();
  void Render();
  void AddEnemy(Enemy* enemy);
  void RemoveEnemy(Enemy* enemy);

 private:
  std::vector<Enemy*> enemies_;
};