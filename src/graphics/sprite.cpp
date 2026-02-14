#include "sprite.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>

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

Sprite::Sprite(const char* path, Dimension dimension)
    : path_{path}, dimension_{dimension} {}

bool Sprite::LoadSpriteSheet() {
  texture_ = Cache::GetInstance()->GetOrCreateTexture(path_);
  if (texture_ == nullptr) {
    Logger::Error("Sprite", std::string("Failed to load texture: ") + path_);
    return false;
  }

  float texture_width{0.0F};
  float texture_height{0.0F};
  if (!SDL_GetTextureSize(texture_, &texture_width, &texture_height)) {
    Logger::Error("Sprite",
                  std::string("SDL_QueryTexture failed: ") + SDL_GetError());
    return false;
  }

  columns_ =
      static_cast<int>(texture_width / static_cast<float>(dimension_.width));

  ;
  if (columns_ <= 0) {
    columns_ = 1;
  }

  rows_ =
      static_cast<int>(texture_height / static_cast<float>(dimension_.height));
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

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void Sprite::RenderSprite(int sprite_index, Sprite::Coordinate coordinate,
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

  SDL_FRect src;
  src.x = static_cast<float>(col * dimension_.width);
  src.y = static_cast<float>(row * dimension_.height);
  src.w = static_cast<float>(dimension_.width);
  src.h = static_cast<float>(dimension_.height);

  SDL_FRect dst;
  dst.x = static_cast<float>(coordinate.x_pos);
  dst.y = static_cast<float>(coordinate.y_pos);
  dst.w = static_cast<float>(dimension_.width * Constants::SPRITE_SCALE);
  dst.h = static_cast<float>(dimension_.height * Constants::SPRITE_SCALE);

  if (invert) {
    const SDL_FlipMode flip = invert ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderTextureRotated(Renderer::renderer_, texture_, &src, &dst, 0.0,
                             nullptr, flip);
  } else {
    if (!SDL_RenderTexture(Renderer::renderer_, texture_, &src, &dst)) {
      Logger::Error("Sprite",
                    std::string("Failed to render sprite: ") + SDL_GetError());
    }
  }

#ifdef DEBUG_MODE
  // Draw red border so you can see tile boundaries.
  Uint8 prev_r, prev_g, prev_b, prev_a;
  SDL_GetRenderDrawColor(Renderer::renderer_, &prev_r, &prev_g, &prev_b,
                         &prev_a);
  SDL_SetRenderDrawColor(Renderer::renderer_, 255, 0, 0, 255);
  SDL_RenderRect(Renderer::renderer_, &dst);
  SDL_SetRenderDrawColor(Renderer::renderer_, prev_r, prev_g, prev_b, prev_a);
#endif  // DEBUG_MODE
}

// TODO(fernandoramirez): Generalize for any number of frames and frame rate.
void Sprite::RenderAnimatedSprite(Sprite::Coordinate coordinate) const {
  // Simple animation by cycling through frames.
  static Uint64 last_time = 0;
  static int current_frame = 0;
  const Uint64 current_time = SDL_GetTicks();
  const Uint64 FRAME_DELAY = 140;
  if (current_time - last_time >= FRAME_DELAY) {
    current_frame = (current_frame + 1) % sprite_count_;
    last_time = current_time;
  }
  RenderSprite(current_frame, coordinate);
}

void Sprite::RenderTileMap(
    const std::array<int, Constants::MAP_ROWS_BY_COLUMNS>& tile_map) const {
  if (texture_ == nullptr) {
    return;
  }
  const int scaled_tile_width = dimension_.width * Constants::SPRITE_SCALE;
  const int scaled_tile_height = dimension_.height * Constants::SPRITE_SCALE;
  for (const int row : std::ranges::iota_view{0, Constants::MAP_ROWS}) {
    for (const int column : std::ranges::iota_view{0, Constants::MAP_COLUMNS}) {
      const int tile = tile_map.at(
          static_cast<size_t>(Math::GetRowMajorOrderIndex(row, column)));
      // Skip negative tiles as they are reserved for empty tiles.
      if (tile < 0) {
        continue;
      }
      RenderSprite(tile, Sprite::Coordinate{.x_pos = column * scaled_tile_width,
                                            .y_pos = row * scaled_tile_height});
    }
  }
}