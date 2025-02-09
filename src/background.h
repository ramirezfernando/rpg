#pragma once

#include "game.h"

class Background {
 public:
  Background(const char* file_path);
  ~Background();
  void Update();
  void Render();

 private:
  SDL_Texture* background_texture_;
  SDL_Rect src_rect_, dest_rect_;
  int x_pos_ = 0, y_pos_ = 0;
};