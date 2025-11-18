#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class SpriteSheetRenderer {
 public:
  SpriteSheetRenderer(const char* path, int tile_width, int tile_height,
                      int margin = 0, int spacing = 0);
  ~SpriteSheetRenderer();
  bool LoadSpriteSheet();
  void RenderSpriteSheetItem(int tile_index, int dst_x, int dst_y,
                             int scale = 1);
  void RenderAnimatedSpriteSheetItem(int dst_x, int dst_y, int scale = 1);
  void RenderSpriteSheet(const int* tile_map, int sprite_columns,
                         int sprite_rows, int dst_x = 0, int dst_y = 0,
                         int scale = 1);

 private:
  const char* path_;
  SDL_Texture* texture_;
  int tile_width_;
  int tile_height_;
  int margin_;
  int spacing_;
  int columns_;
  int rows_;
  int tile_count_;
};