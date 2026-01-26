#include "cache.h"

#include <iostream>

#include "util/logger.h"
#include "util/util.h"

Cache* Cache::GetInstance() {
  static Cache instance;  // Thread-safe in C++11+.
  return &instance;
}

Cache::~Cache() {
  Clear();
}

SDL_Texture* Cache::GetTexture(const char* file_name) {
  if (!file_name) {
    Logger::Error("Cache", "file_name is null");
    return nullptr;
  }

  std::string key(file_name);

  // Check if texture is already cached.
  if (texture_cache_.find(key) != texture_cache_.end()) {
    Logger::Debug("Cache", std::string("Texture cached: ") + file_name);
    return texture_cache_[key];
  }

  // Load texture using Util::LoadTexture (handles all file I/O and error
  // checking).
  SDL_Texture* texture = Util::LoadTexture(file_name);
  if (!texture) {
    Logger::Error("Cache", std::string("Failed to load texture: ") + file_name);
    return nullptr;
  }

  // Cache the texture.
  texture_cache_[key] = texture;

  Logger::Debug("Cache", std::string("Texture loaded: ") + file_name);

  return texture;
}

Sprite* Cache::GetSprite(const char* file_path, int sprite_width,
                         int sprite_height) {
  if (!file_path) {
    Logger::Error("Cache", "path is null");
    return nullptr;
  }

  std::string key(file_path);

  // Check if sprite sheet is already cached.
  if (sprite_sheet_cache_.find(key) != sprite_sheet_cache_.end()) {
    Logger::Debug("Cache", std::string("Sprite sheet cached: ") + file_path);
    return sprite_sheet_cache_[key].get();
  }

  // Create and load sprite sheet.
  auto renderer =
      std::make_unique<Sprite>(file_path, sprite_width, sprite_height, 0, 0);

  if (!renderer->LoadSpriteSheet()) {
    Logger::Error("Cache",
                  std::string("Failed to load sprite sheet: ") + file_path);
    return nullptr;
  }

  // Cache the sprite sheet and return raw pointer.
  Sprite* raw_ptr = renderer.get();
  sprite_sheet_cache_[key] = std::move(renderer);

  Logger::Debug("Cache", std::string("Sprite sheet loaded: ") + file_path);

  return raw_ptr;
}

void Cache::Clear() {
  // Destroy all cached textures.
  for (auto& pair : texture_cache_) {
    if (pair.second) {
      SDL_DestroyTexture(pair.second);
    }
  }
  texture_cache_.clear();

  // Clear sprite sheet cache (unique_ptrs will auto-destruct).
  sprite_sheet_cache_.clear();

  Logger::Debug("Cache", "Resource cache cleared");
}
