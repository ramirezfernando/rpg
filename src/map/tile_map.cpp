#include <SDL2/SDL.h>
#include <iostream>

#include "map/tile_map.h"
#include "util/util.h"

TileMap::TileMap(const char* path, int tile_width, int tile_height, int margin,
                 int spacing)
    : path_(path),
      texture_(nullptr),
      tile_width_(tile_width),
      tile_height_(tile_height),
      margin_(margin),
      spacing_(spacing),
      columns_(0) {}

TileMap::~TileMap() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}

bool TileMap::Load() {
  texture_ = Util::LoadTexture(path_);
  if (!texture_) {
    std::cerr << "Tile map failed to load texture: " << path_ << std::endl;
    return false;
  }

  int texture_width = 0, texture_height = 0;
  if (SDL_QueryTexture(texture_, nullptr, nullptr, &texture_width,
                       &texture_height) != 0) {
    std::cerr << "SDL_QueryTexture failed: " << SDL_GetError() << std::endl;
    return false;
  }

  // Compute columns/rows using tile size, margin and spacing.
  columns_ =
      (texture_width - 2 * margin_ + spacing_) / (tile_width_ + spacing_);
  if (columns_ <= 0)
    columns_ = 1;

  rows_ = (texture_height - 2 * margin_ + spacing_) / (tile_height_ + spacing_);
  if (rows_ <= 0)
    rows_ = 1;

  tile_count_ = columns_ * rows_;

  std::cout << "Tile map loaded: " << path_ << " tex=" << texture_width << "x"
            << texture_height << " cols=" << columns_ << " rows=" << rows_
            << " tiles=" << tile_count_ << std::endl;

  return true;
}

void TileMap::RenderTile(int tile_index, int dst_x, int dst_y, int scale) {
  if (!texture_)
    return;
  // Negative reserved for empty tiles.
  if (tile_index < 0)
    return;
  if (tile_index >= tile_count_) {
    std::cerr << "Tile map: tile_index " << tile_index << " out of range (0.."
              << (tile_count_ - 1) << ")\n";
    return;
  }

  int col = tile_index % columns_;
  int row = tile_index / columns_;

  SDL_Rect src;
  src.x = margin_ + col * (tile_width_ + spacing_);
  src.y = margin_ + row * (tile_height_ + spacing_);
  src.w = tile_width_;
  src.h = tile_height_;

  SDL_Rect dst;
  dst.x = dst_x;
  dst.y = dst_y;
  dst.w = tile_width_ * scale;
  dst.h = tile_height_ * scale;

  SDL_RenderCopy(Game::renderer_, texture_, &src, &dst);

  // Draw red border so you can see tile boundaries (for debugging).
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(Game::renderer_, &prev_r, &prev_g, &prev_b, &prev_a);
  SDL_SetRenderDrawColor(Game::renderer_, 255, 0, 0, 255);
  SDL_RenderDrawRect(Game::renderer_, &dst);
  SDL_SetRenderDrawColor(Game::renderer_, prev_r, prev_g, prev_b, prev_a);
}

void TileMap::RenderTileMap(const int* tile_map, int tile_map_columns,
                            int tile_map_rows, int dst_x, int dst_y,
                            int scale) {
  if (!texture_)
    return;
  if (!tile_map)
    return;

  for (int y = 0; y < tile_map_rows; ++y) {
    for (int x = 0; x < tile_map_columns; ++x) {
      int idx = tile_map[y * tile_map_columns + x];
      // Skip negative tiles as they are reserved for empty tiles.
      if (idx < 0)
        continue;
      RenderTile(idx, dst_x + x * tile_width_ * scale,
                 dst_y + y * tile_height_ * scale, scale);
    }
  }
}