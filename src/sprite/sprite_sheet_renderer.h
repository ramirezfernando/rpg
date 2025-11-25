#pragma once

#include <SDL2/SDL.h>

// This class manages loading and rendering of sprite sheets.
class SpriteSheetRenderer {
 public:
  SpriteSheetRenderer(const char* path, int sprite_width, int sprite_height,
                      int margin = 0, int spacing = 0);
  ~SpriteSheetRenderer() = default;

  // Loads and sets up the variables for the sprite sheet.
  bool LoadSpriteSheet();
  // Renders a specific sprite from the sprite sheet at the given position.
  void RenderSprite(int sprite_index, int dst_x, int dst_y, int scale = 3);
  // Renders through an x by 1 sprite sheet as an animation.
  void RenderAnimatedSprite(int dst_x, int dst_y, int scale = 3);
  // Renders a tile map given an array of tile indices.
  void RenderTileMap(const int* tile_map, int tile_map_columns,
                     int tile_map_rows, int dst_x = 0, int dst_y = 0,
                     int scale = 3);

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