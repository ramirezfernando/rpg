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
                    bool invert = false);
  // Renders through an x by 1 sprite sheet as an animation.
  void RenderAnimatedSprite(int dst_x, int dst_y);
  // Renders a tile map given an array of tile indices.
  void RenderTileMap(
      const std::array<int, Constants::MAP_ROWS_BY_COLUMNS>& tile_map);
  // Getters
  char* GetPath() const { return path_; }
  int GetSpriteWidth() const { return sprite_width_; }
  int GetSpriteHeight() const { return sprite_height_; }
  int GetMargin() const { return margin_; }
  int GetSpacing() const { return spacing_; }
  int GetColumns() const { return columns_; }
  int GetRows() const { return rows_; }
  int GetSpriteCount() const { return sprite_count_; }

  // Setters
  void SetPath(const char* path) { path_ = path; }

 private:
  const char* path_;
  int sprite_width_;
  int sprite_height_;
  int margin_;
  int spacing_;

  SDL_Texture* texture_{nullptr};
  int columns_{0};
  int rows_{0};
  int sprite_count_{0};
};