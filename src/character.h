#pragma once

#include "constants/asset_constants.h"
#include "game.h"

class Character {
 public:
  virtual ~Character();
  void Update();
  void Render();
  void SetFolderPath(const char* folder_path);
  virtual void SetFolderPathFromDirection(Constants::Direction direction) = 0;
  void SetShouldAttack(bool should_attack);
  void SetXPos(int x_pos);
  void SetYPos(int y_pos);
  int GetXPos();
  int GetYPos();
  bool IsWithinBounds(int x_pos, int y_pos);
  void Attack();

 protected:
  SDL_Texture* character_texture_;
  SDL_Rect src_rect_, dest_rect_;
  int x_pos_, y_pos_, frames_, delay_, count_;
  const char* folder_path_;
  bool should_attack_ = false;
};