#pragma once

#include "constants/asset_constants.h"
#include "enemies/enemy.h"
#include "game.h"

class Character {
 public:
  virtual ~Character();
  void Update(Enemy* enemy);
  void Render();
  void SetFolderPath(const char* folder_path) { folder_path_ = folder_path; }
  virtual void SetFolderPathFromDirection(Constants::Direction direction) = 0;
  void SetShouldAttack(bool should_attack) { should_attack_ = should_attack; }
  void SetXPos(int x_pos);
  void SetYPos(int y_pos);
  int GetXPos() { return x_pos_; }
  int GetYPos() { return y_pos_; }
  void SetDirectionFacing(Constants::Direction direction) {
    direction_facing_ = direction;
  }

 private:
  void Attack(Enemy* enemy);
  bool IsWithinWindowBounds();
  bool IsWithinAttackRange(int enemy_x_pos, int enemy_y_pos);
  bool IsFacingEnemy(int enemy_x_pos, int enemy_y_pos);
  bool ShouldUpdateTexture(Uint32 current_time);
  bool ShouldIncrementTexture();

 protected:
  SDL_Texture* character_texture_;
  SDL_Rect src_rect_, dest_rect_;
  const char* folder_path_;
  int x_pos_, y_pos_, frames_, delay_ = 70, count_ = 0;
  Uint32 last_frame_time_ = 0;
  bool should_attack_ = false;
  Constants::Direction direction_facing_;
};