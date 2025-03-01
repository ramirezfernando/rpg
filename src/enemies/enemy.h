#pragma once

#include "constants/asset_constants.h"
#include "game.h"

// TODO: Create a base class for the enemy and character classes?
class Enemy {
 public:
  virtual ~Enemy();
  void Update(int character_x_pos, int character_y_pos);
  void Render();
  void SetXPos(int x_pos);
  void SetYPos(int y_pos);
  int GetXPos() { return x_pos_; }
  int GetYPos() { return y_pos_; }
  void SetHealth(int health) { health_ = health; }
  int GetHealth() { return health_; }
  void FollowCharacter(int character_x_pos, int character_y_pos);

 protected:
  SDL_Texture* enemy_texture_;
  SDL_Rect src_rect_, dest_rect_;
  const char* folder_path_;
  int x_pos_, y_pos_, frames_, health_, delay_ = 70, count_ = 0;
};