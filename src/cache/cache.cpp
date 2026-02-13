#include "cache.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <memory>
#include <utility>

#include "graphics/renderer.h"
#include "graphics/sprite.h"
#include "util/logger.h"

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

SDL_Texture* Cache::GetOrCreateTexture(const char* file_name) {
  if (file_name == nullptr) {
    Logger::Error("Cache", "file_name is null");
    return nullptr;
  }

  const std::string key{file_name};

  // Check if texture is already cached.
  if (texture_cache_.contains(key)) {
    Logger::Debug("Cache", std::string("Texture cached: ") + file_name);
    return texture_cache_[key];
  }

  // Create texture since it's not cached.
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
  SDL_Texture* texture = CreateTexture(file_name);
  if (texture == nullptr) {
    Logger::Error("Cache", std::string("Failed to load texture: ") + file_name);
    return nullptr;
  }

  // Cache the texture.
  texture_cache_[key] = texture;
  Logger::Debug("Cache", std::string("Texture loaded: ") + file_name);

  return texture;
}

const Sprite* Cache::GetOrCreateSpriteSheet(const char* file_path,
                                            Sprite::Dimension dimension) {
  if (file_path == nullptr) {
    Logger::Error("Cache", "path is null");
    return nullptr;
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
    Logger::Error("Cache",
                  std::string("Failed to load sprite sheet: ") + file_path);
    return nullptr;
  }

  // Cache the sprite sheet.
  const Sprite* raw_ptr = sprite.get();
  sprite_sheet_cache_[key] = std::move(sprite);
  Logger::Debug("Cache", std::string("Sprite sheet loaded: ") + file_path);

  return raw_ptr;
}

// NOLINTNEXTLINE(misc-const-correctness)
SDL_Texture* Cache::CreateTexture(const char* file_name) {
  SDL_Surface* tmp_surface = IMG_Load(file_name);
  // NOLINTNEXTLINE(misc-const-correctness)
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(Renderer::renderer_, tmp_surface);
  SDL_FreeSurface(tmp_surface);
  return texture;
}