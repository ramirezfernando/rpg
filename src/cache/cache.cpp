#include "cache.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>

#include <expected>
#include <memory>
#include <string>
#include <utility>

#include "graphics/renderer.h"
#include "graphics/sprite.h"
#include "util/logger.h"

namespace {}

Cache* Cache::GetInstance() {
  static Cache instance;  // Thread-safe in C++11+.
  return &instance;
}

Cache::~Cache() {
  // Destroy all cached textures.
  for (auto& pair : texture_cache_) {
    if (pair.second != nullptr) {
      SDL_DestroyTexture(pair.second);
    }
  }
  texture_cache_.clear();
  sprite_sheet_cache_.clear();
  Logger::Debug("Cache", "Resource cache cleared");
}

std::expected<SDL_Texture*, std::string> Cache::GetOrCreateTexture(
    const char* file_name) {
  if (file_name == nullptr) {
    return std::unexpected("file_name is null");
  }

  const std::string key{file_name};

  // Check if texture is already cached.
  if (texture_cache_.contains(key)) {
    Logger::Debug("Cache", std::string("Texture cached: ") + file_name);
    return texture_cache_[key];
  }

  // Create texture since it's not cached.
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
  std::expected<SDL_Texture*, std::string> texture_result =
      CreateTexture(file_name);
  if (!texture_result.has_value()) {
    return std::unexpected(std::string("Failed to load texture: ") + file_name +
                           " - " + texture_result.error());
  }

  SDL_Texture* texture = texture_result.value();

  // Cache the texture.
  texture_cache_[key] = texture;
  Logger::Debug("Cache", std::string("Texture loaded: ") + file_name);

  return texture;
}

std::expected<const Sprite*, std::string> Cache::GetOrCreateSpriteSheet(
    const char* file_path, Sprite::Dimension dimension) {
  if (file_path == nullptr) {
    return std::unexpected("path is null");
  }

  const std::string key{file_path};

  // Check if sprite is already cached.
  if (sprite_sheet_cache_.contains(key)) {
    Logger::Debug("Cache", std::string("Sprite sheet cached: ") + file_path);
    return sprite_sheet_cache_[key].get();
  }

  // Create and load sprite sheet.
  auto sprite = std::make_unique<Sprite>(file_path, dimension);

  if (!sprite->LoadSpriteSheet()) {
    return std::unexpected(std::string("Failed to load sprite sheet: ") +
                           file_path);
  }

  // Cache the sprite sheet.
  const Sprite* raw_ptr = sprite.get();
  sprite_sheet_cache_[key] = std::move(sprite);
  Logger::Debug("Cache", std::string("Sprite sheet loaded: ") + file_path);

  return raw_ptr;
}

// NOLINTNEXTLINE(misc-const-correctness)
std::expected<SDL_Texture*, std::string> Cache::CreateTexture(
    const char* file_name) {
  SDL_Surface* tmp_surface = IMG_Load(file_name);
  if (tmp_surface == nullptr) {
    return std::unexpected(std::string("Failed to load surface: ") +
                           SDL_GetError());
  }

  // Convert to RGBA format if needed. Sprites such as hotbar are not rendered
  // unless it's converted to RGBA format.
  SDL_Surface* converted_surface =
      SDL_ConvertSurface(tmp_surface, SDL_PIXELFORMAT_RGBA8888);
  SDL_DestroySurface(tmp_surface);
  if (converted_surface == nullptr) {
    return std::unexpected(std::string("Failed to convert surface: ") +
                           SDL_GetError());
  }

  // NOLINTNEXTLINE(misc-const-correctness)
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(Renderer::renderer_, converted_surface);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_PIXELART);
  SDL_DestroySurface(converted_surface);
  return texture;
}