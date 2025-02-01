#include <string>
#include "game.h"

using namespace std;

#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
 public:
  void Update();
  void Render();
  void Clean();
  void SetFilePath(const char* file_path) { file_path_ = file_path; }
  void SetXPos(int x_pos) { x_pos_ = x_pos; }
  void SetYPos(int y_pos) { y_pos_ = y_pos; }
  int GetXPos() { return x_pos_; }
  int GetYPos() { return y_pos_; }

 protected:
  SDL_Texture* character_texture_;
  SDL_Rect src_rect_, dest_rect_;
  int x_pos_, y_pos_, frames_, delay_, count_;
  const char* file_path_;
};

#endif