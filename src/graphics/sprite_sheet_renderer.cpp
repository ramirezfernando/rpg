#include "sprite_sheet_renderer.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <sstream>

#include "core/game.h"  // For Game::renderer_
#include "resource/resource_manager.h"
#include "util/constants.h"
#include "util/logger.h"

SpriteSheetRenderer::SpriteSheetRenderer(const char* path, int sprite_width,
                                         int sprite_height, int margin,
                                         int spacing)
    : path_(path),
      texture_(nullptr),
      sprite_width_(sprite_width),
      sprite_height_(sprite_height),
      margin_(margin),
      spacing_(spacing),
      columns_(0) {}

bool SpriteSheetRenderer::LoadSpriteSheet() {
  texture_ = ResourceManager::GetInstance().GetTexture(path_);
  if (!texture_) {
    Logger::Error("SpriteSheetRenderer",
                  std::string("Failed to load texture: ") + path_);
    return false;
  }

  int texture_width = 0, texture_height = 0;
  if (SDL_QueryTexture(texture_, nullptr, nullptr, &texture_width,
                       &texture_height) != 0) {
    Logger::Error("SpriteSheetRenderer",
                  std::string("SDL_QueryTexture failed: ") + SDL_GetError());
    return false;
  }

  // Compute columns/rows using tile size, margin and spacing.
  columns_ =
      (texture_width - 2 * margin_ + spacing_) / (sprite_width_ + spacing_);
  if (columns_ <= 0) {
    columns_ = 1;
  }

  rows_ =
      (texture_height - 2 * margin_ + spacing_) / (sprite_height_ + spacing_);
  if (rows_ <= 0) {
    rows_ = 1;
  }

  sprite_count_ = columns_ * rows_;

  std::ostringstream oss;
  oss << "Sprite sheet loaded: " << path_ << " tex=" << texture_width << "x"
      << texture_height << " cols=" << columns_ << " rows=" << rows_
      << " tiles=" << sprite_count_;
  Logger::Debug("SpriteSheetRenderer", oss.str());

  return true;
}

void SpriteSheetRenderer::RenderSprite(int sprite_index, int dst_x, int dst_y,
                                       bool invert) {
  if (!texture_) {
    return;
  }
  // Negative reserved for empty tiles.
  if (sprite_index < 0) {
    return;
  }
  if (sprite_index >= sprite_count_) {
    std::ostringstream oss;
    oss << "RenderSprite: sprite_index " << sprite_index << " out of range (0.."
        << (sprite_count_ - 1) << ")";
    Logger::Warning("SpriteSheetRenderer", oss.str());
    return;
  }

  int col = sprite_index % columns_;
  int row = sprite_index / columns_;

  SDL_Rect src;
  src.x = margin_ + col * (sprite_width_ + spacing_);
  src.y = margin_ + row * (sprite_height_ + spacing_);
  src.w = sprite_width_;
  src.h = sprite_height_;

  SDL_Rect dst;
  dst.x = dst_x;
  dst.y = dst_y;
  dst.w = sprite_width_ * Constants::SPRITE_SCALE;
  dst.h = sprite_height_ * Constants::SPRITE_SCALE;

  if (invert) {
    SDL_RendererFlip flip = invert ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(Game::renderer_, texture_, &src, &dst, 0.0, NULL, flip);
  } else {
    SDL_RenderCopy(Game::renderer_, texture_, &src, &dst);
  }

#if defined(DEBUG_MODE)
  // Draw red border so you can see tile boundaries.
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(Game::renderer_, &prev_r, &prev_g, &prev_b, &prev_a);
  SDL_SetRenderDrawColor(Game::renderer_, 255, 0, 0, 255);
  SDL_RenderDrawRect(Game::renderer_, &dst);
  SDL_SetRenderDrawColor(Game::renderer_, prev_r, prev_g, prev_b, prev_a);
#endif  // DEBUG_MODE
}

// TODO: Generalize for any number of frames and frame rate.
void SpriteSheetRenderer::RenderAnimatedSprite(int dst_x, int dst_y) {
  // Simple animation by cycling through frames.
  static Uint32 last_time = 0;
  static int current_frame = 0;
  Uint32 current_time = SDL_GetTicks();
  const Uint32 FRAME_DELAY = 140;
  if (current_time - last_time >= FRAME_DELAY) {
    current_frame = (current_frame + 1) % sprite_count_;
    last_time = current_time;
  }
  RenderSprite(current_frame, dst_x, dst_y);
}

void SpriteSheetRenderer::RenderTileMap(
    const std::array<int, Constants::MAP_ROWS_BY_COLUMNS> tile_map,
    int tile_map_columns, int tile_map_rows, int dst_x, int dst_y) {
  if (!texture_) {
    return;
  }

  for (int y = 0; y < tile_map_rows; ++y) {
    for (int x = 0; x < tile_map_columns; ++x) {
      int idx = tile_map[y * tile_map_columns + x];
      // Skip negative tiles as they are reserved for empty tiles.
      if (idx < 0) {
        continue;
      }
      RenderSprite(idx, dst_x + x * sprite_width_ * Constants::SPRITE_SCALE,
                   dst_y + y * sprite_height_ * Constants::SPRITE_SCALE);
    }
  }
}