#include "sprite.h"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <sstream>

#include "cache/cache.h"
#include "constants/map_constants.h"
#include "constants/sprite_constants.h"
#include "renderer.h"
#include "util/logger.h"
#include "util/math.h"

Sprite::Sprite(const char* path, int sprite_width, int sprite_height,
               int margin, int spacing)
    : path_{path},
      sprite_width_{sprite_width},
      sprite_height_{sprite_height},
      margin_{margin},
      spacing_{spacing} {}

bool Sprite::LoadSpriteSheet() {
  texture_ = Cache::GetInstance()->GetOrCreateTexture(path_);
  if (texture_ == nullptr) {
    Logger::Error("Sprite", std::string("Failed to load texture: ") + path_);
    return false;
  }

  int texture_width = 0, texture_height = 0;
  if (SDL_QueryTexture(texture_, nullptr, nullptr, &texture_width,
                       &texture_height) != 0) {
    Logger::Error("Sprite",
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
  Logger::Debug("Sprite", oss.str());

  return true;
}

void Sprite::RenderSprite(int sprite_index, int dst_x, int dst_y,
                          bool invert) const {
  if (texture_ == nullptr) {
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
    Logger::Warning("Sprite", oss.str());
    return;
  }

  const int col = sprite_index % columns_;
  const int row = sprite_index / columns_;

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
    const SDL_RendererFlip flip = invert ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(Renderer::renderer_, texture_, &src, &dst, 0.0, nullptr,
                     flip);
  } else {
    SDL_RenderCopy(Renderer::renderer_, texture_, &src, &dst);
  }

#if defined(DEBUG_MODE)
  // Draw red border so you can see tile boundaries.
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(Renderer::renderer_, &prev_r, &prev_g, &prev_b,
                         &prev_a);
  SDL_SetRenderDrawColor(Renderer::renderer_, 255, 0, 0, 255);
  SDL_RenderDrawRect(Renderer::renderer_, &dst);
  SDL_SetRenderDrawColor(Renderer::renderer_, prev_r, prev_g, prev_b, prev_a);
#endif  // DEBUG_MODE
}

// TODO(fernandoramirez): Generalize for any number of frames and frame rate.
void Sprite::RenderAnimatedSprite(int dst_x, int dst_y) const {
  // Simple animation by cycling through frames.
  static Uint32 last_time = 0;
  static int current_frame = 0;
  const Uint32 current_time = SDL_GetTicks();
  const Uint32 FRAME_DELAY = 140;
  if (current_time - last_time >= FRAME_DELAY) {
    current_frame = (current_frame + 1) % sprite_count_;
    last_time = current_time;
  }
  RenderSprite(current_frame, dst_x, dst_y);
}

void Sprite::RenderTileMap(
    const std::array<int, Constants::MAP_ROWS_BY_COLUMNS>& tile_map) const {
  if (texture_ == nullptr) {
    return;
  }
  const int scaled_tile_width = sprite_width_ * Constants::SPRITE_SCALE;
  const int scaled_tile_height = sprite_height_ * Constants::SPRITE_SCALE;
  for (const int row : std::ranges::iota_view{0, Constants::MAP_ROWS}) {
    for (const int column : std::ranges::iota_view{0, Constants::MAP_COLUMNS}) {
      const int tile = tile_map.at(
          static_cast<size_t>(Math::GetRowMajorOrderIndex(row, column)));
      // Skip negative tiles as they are reserved for empty tiles.
      if (tile < 0) {
        continue;
      }
      RenderSprite(tile, column * scaled_tile_width, row * scaled_tile_height);
    }
  }
}