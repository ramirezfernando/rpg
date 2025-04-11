#include "spawner.h"

Spawner::Spawner() {}

Spawner::~Spawner() {
  for (auto enemy : enemies_) {
    delete enemy;
  }
  enemies_.clear();
}

void Spawner::Update() {
  for (auto enemy : enemies_) {
    enemy->Update(0, 0);  // Update with dummy values for now
  }
}

void Spawner::Render() {
  for (auto enemy : enemies_) {
    enemy->Render();
  }
}

void Spawner::AddEnemy(Enemy* enemy) {
  enemies_.push_back(enemy);
}

void Spawner::RemoveEnemy(Enemy* enemy) {
  auto it = std::find(enemies_.begin(), enemies_.end(), enemy);
  if (it != enemies_.end()) {
    delete *it;
    enemies_.erase(it);
  }
}