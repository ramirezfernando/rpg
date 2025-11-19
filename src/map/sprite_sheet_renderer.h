#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

// This class manages loading and rendering of sprite sheets.
class SpriteSheetRenderer {
 public:
  SpriteSheetRenderer(const char* path, int sprite_width, int sprite_height,
                      int margin = 0, int spacing = 0);
  ~SpriteSheetRenderer();

  bool LoadSpriteSheet();
  void RenderSprite(int sprite_index, int dst_x, int dst_y, int scale = 1);
  void RenderAnimatedSprite(int dst_x, int dst_y, int scale = 1);
  void RenderTileMap(const int* tile_map, int tile_map_columns,
                     int tile_map_rows, int dst_x = 0, int dst_y = 0,
                     int scale = 1);

 private:
  const char* path_;
  SDL_Texture* texture_;
  int sprite_width_;
  int sprite_height_;
  int margin_;
  int spacing_;
  int columns_;
  int rows_;
  int sprite_count_;
};