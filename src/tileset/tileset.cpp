#include "tileset/tileset.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "game.h"
#include "util/util.h"

Tileset::Tileset(const char* path, int tile_w, int tile_h, int margin,
                 int spacing)
    : path_(path),
      texture_(nullptr),
      tile_w_(tile_w),
      tile_h_(tile_h),
      margin_(margin),
      spacing_(spacing),
      columns_(0) {}

Tileset::~Tileset() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}

bool Tileset::Load() {
  texture_ = Util::LoadTexture(path_);
  if (!texture_) {
    std::cerr << "Tileset: failed to load texture: " << path_ << std::endl;
    return false;
  }

  int tex_w = 0, tex_h = 0;
  if (SDL_QueryTexture(texture_, nullptr, nullptr, &tex_w, &tex_h) != 0) {
    std::cerr << "SDL_QueryTexture failed: " << SDL_GetError() << std::endl;
    return false;
  }

  // Compute columns/rows using tile size, margin and spacing.
  columns_ = (tex_w - 2 * margin_ + spacing_) / (tile_w_ + spacing_);
  if (columns_ <= 0)
    columns_ = 1;

  rows_ = (tex_h - 2 * margin_ + spacing_) / (tile_h_ + spacing_);
  if (rows_ <= 0)
    rows_ = 1;

  tile_count_ = columns_ * rows_;

  std::cout << "Tileset loaded: " << path_ << " tex=" << tex_w << "x" << tex_h
            << " cols=" << columns_ << " rows=" << rows_
            << " tiles=" << tile_count_ << std::endl;

  return true;
}

void Tileset::RenderTile(int tile_index, int dst_x, int dst_y, int scale) {
  if (!texture_)
    return;
  // Negative reserved for empty tiles.
  if (tile_index < 0)
    return;
  if (tile_index >= tile_count_) {
    std::cerr << "Tileset::RenderTile: tile_index " << tile_index
              << " out of range (0.." << (tile_count_ - 1) << ")\n";
    return;
  }

  int col = tile_index % columns_;
  int row = tile_index / columns_;

  SDL_Rect src;
  src.x = margin_ + col * (tile_w_ + spacing_);
  src.y = margin_ + row * (tile_h_ + spacing_);
  src.w = tile_w_;
  src.h = tile_h_;

  SDL_Rect dst;
  dst.x = dst_x;
  dst.y = dst_y;
  dst.w = tile_w_ * scale;
  dst.h = tile_h_ * scale;

  SDL_RenderCopy(Game::renderer_, texture_, &src, &dst);

  // Draw red border so you can see tile boundaries (for debugging).
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(Game::renderer_, &prev_r, &prev_g, &prev_b, &prev_a);
  SDL_SetRenderDrawColor(Game::renderer_, 255, 0, 0, 255);
  SDL_RenderDrawRect(Game::renderer_, &dst);
  SDL_SetRenderDrawColor(Game::renderer_, prev_r, prev_g, prev_b, prev_a);
}

void Tileset::RenderMap(const std::vector<int>& map, int map_w, int map_h,
                        int dst_x, int dst_y, int scale) {
  if (!texture_)
    return;
  if ((int)map.size() < map_w * map_h)
    return;

  for (int y = 0; y < map_h; ++y) {
    for (int x = 0; x < map_w; ++x) {
      int idx = map[y * map_w + x];
      // Skip negative tiles as they are reserved for empty tiles.
      if (idx < 0)
        continue;
      RenderTile(idx, dst_x + x * tile_w_ * scale, dst_y + y * tile_h_ * scale,
                 scale);
    }
  }
}