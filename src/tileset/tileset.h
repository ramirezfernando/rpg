#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Tileset {
 public:
  Tileset(const char* path, int tile_w, int tile_h, int margin = 0,
          int spacing = 0);
  ~Tileset();
  bool Load();
  void RenderTile(int tile_index, int dst_x, int dst_y, int scale = 1);
  void RenderMap(const std::vector<int>& map, int map_w, int map_h,
                 int dst_x = 0, int dst_y = 0, int scale = 1);

 private:
  const char* path_;
  SDL_Texture* texture_;
  int tile_w_;
  int tile_h_;
  int margin_;
  int spacing_;
  int columns_;
  int rows_;
  int tile_count_;
};