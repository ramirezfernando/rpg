#pragma once

#include "game.h"

class Background {
 public:
  Background(const char* file_path, int x_pos, int y_pos);
  void Update();
  void Render();
  void Clean();

 private:
  SDL_Texture* background_texture_;
  SDL_Rect src_rect_, dest_rect_;
  int x_pos_, y_pos_;
};