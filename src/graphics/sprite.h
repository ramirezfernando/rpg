#pragma once

#include <SDL2/SDL.h>

#include <array>

#include "constants/map_constants.h"

// This class manages loading and rendering of sprite sheets.
class Sprite {
 public:
  Sprite(const char* path, int sprite_width, int sprite_height, int margin = 0,
         int spacing = 0);
  ~Sprite() = default;
  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;
  Sprite(Sprite&&) = delete;
  Sprite& operator=(Sprite&&) = delete;

  // Loads and sets up the variables for the sprite sheet.
  bool LoadSpriteSheet();
  // Renders a specific sprite from the sprite sheet at the given position.
  void RenderSprite(int sprite_index, int dst_x, int dst_y,
                    bool invert = false) const;
  // Renders through an x by 1 sprite sheet as an animation.
  void RenderAnimatedSprite(int dst_x, int dst_y) const;
  // Renders a tile map given an array of tile indices.
  void RenderTileMap(
      const std::array<int, Constants::MAP_ROWS_BY_COLUMNS>& tile_map) const;

  // Getters:
  [[nodiscard]] const char* GetPath() const { return path_; }
  [[nodiscard]] int GetSpriteWidth() const { return sprite_width_; }
  [[nodiscard]] int GetSpriteHeight() const { return sprite_height_; }
  [[nodiscard]] int GetMargin() const { return margin_; }
  [[nodiscard]] int GetSpacing() const { return spacing_; }
  [[nodiscard]] int GetColumns() const { return columns_; }
  [[nodiscard]] int GetRows() const { return rows_; }
  [[nodiscard]] int GetSpriteCount() const { return sprite_count_; }

 private:
  const char* path_;
  const int sprite_width_;
  const int sprite_height_;
  const int margin_;
  const int spacing_;

  const SDL_Texture* texture_{nullptr};
  int columns_{0};
  int rows_{0};
  int sprite_count_{0};
};