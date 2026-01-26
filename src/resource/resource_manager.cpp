#include "resource_manager.h"

#include <iostream>

#include "util/logger.h"
#include "util/util.h"

ResourceManager& ResourceManager::GetInstance() {
  static ResourceManager instance;
  return instance;
}

SDL_Texture* ResourceManager::GetTexture(const char* file_name) {
  if (!file_name) {
    Logger::Error("ResourceManager", "file_name is null");
    return nullptr;
  }

  std::string key(file_name);

  // Check if texture is already cached.
  if (texture_cache_.find(key) != texture_cache_.end()) {
    Logger::Debug("ResourceManager",
                  std::string("Texture cached: ") + file_name);
    return texture_cache_[key];
  }

  // Load texture using Util::LoadTexture (handles all file I/O and error
  // checking).
  SDL_Texture* texture = Util::LoadTexture(file_name);
  if (!texture) {
    Logger::Error("ResourceManager",
                  std::string("Failed to load texture: ") + file_name);
    return nullptr;
  }

  // Cache the texture.
  texture_cache_[key] = texture;

  Logger::Debug("ResourceManager", std::string("Texture loaded: ") + file_name);

  return texture;
}

Sprite* ResourceManager::GetSpriteSheet(const char* path, int sprite_width,
                                        int sprite_height, int margin,
                                        int spacing) {
  if (!path) {
    Logger::Error("ResourceManager", "path is null");
    return nullptr;
  }

  std::string key(path);

  // Check if sprite sheet is already cached.
  if (sprite_sheet_cache_.find(key) != sprite_sheet_cache_.end()) {
    Logger::Debug("ResourceManager",
                  std::string("Sprite sheet cached: ") + path);
    return sprite_sheet_cache_[key].get();
  }

  // Create and load sprite sheet.
  auto renderer = std::make_unique<Sprite>(path, sprite_width, sprite_height,
                                           margin, spacing);

  if (!renderer->LoadSpriteSheet()) {
    Logger::Error("ResourceManager",
                  std::string("Failed to load sprite sheet: ") + path);
    return nullptr;
  }

  // Cache the sprite sheet and return raw pointer.
  Sprite* raw_ptr = renderer.get();
  sprite_sheet_cache_[key] = std::move(renderer);

  Logger::Debug("ResourceManager", std::string("Sprite sheet loaded: ") + path);

  return raw_ptr;
}

void ResourceManager::Clear() {
  // Destroy all cached textures.
  for (auto& pair : texture_cache_) {
    if (pair.second) {
      SDL_DestroyTexture(pair.second);
    }
  }
  texture_cache_.clear();

  // Clear sprite sheet cache (unique_ptrs will auto-destruct).
  sprite_sheet_cache_.clear();

  Logger::Debug("ResourceManager", "Resource cache cleared");
}

ResourceManager::~ResourceManager() {
  Clear();
}
