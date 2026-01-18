#include "resource_manager.h"

#include <iostream>

#include "util/util.h"

ResourceManager& ResourceManager::GetInstance() {
  static ResourceManager instance;
  return instance;
}

SDL_Texture* ResourceManager::GetTexture(const char* file_name) {
  if (!file_name) {
    std::cerr << "Error: file_name is null" << std::endl;
    return nullptr;
  }

  std::string key(file_name);

  // Check if texture is already cached.
  if (texture_cache_.find(key) != texture_cache_.end()) {
#if defined(DEBUG_MODE)
    std::cout << "Loaded texture from cache: " << file_name << std::endl;
#endif
    return texture_cache_[key];
  }

  // Load texture using Util::LoadTexture (handles all file I/O and error
  // checking).
  SDL_Texture* texture = Util::LoadTexture(file_name);
  if (!texture) {
    std::cerr << "Error loading texture " << file_name << std::endl;
    return nullptr;
  }

  // Cache the texture.
  texture_cache_[key] = texture;

#if defined(DEBUG_MODE)
  std::cout << "Loaded texture from file: " << file_name << std::endl;
#endif

  return texture;
}

SpriteSheetRenderer* ResourceManager::GetSpriteSheet(const char* path,
                                                     int sprite_width,
                                                     int sprite_height,
                                                     int margin, int spacing) {
  if (!path) {
    std::cerr << "Error: path is null" << std::endl;
    return nullptr;
  }

  std::string key(path);

  // Check if sprite sheet is already cached.
  if (sprite_sheet_cache_.find(key) != sprite_sheet_cache_.end()) {
#if defined(DEBUG_MODE)
    std::cout << "Loaded sprite sheet from cache: " << path << std::endl;
#endif
    return sprite_sheet_cache_[key].get();
  }

  // Create and load sprite sheet.
  auto renderer = std::make_unique<SpriteSheetRenderer>(
      path, sprite_width, sprite_height, margin, spacing);

  if (!renderer->LoadSpriteSheet()) {
    std::cerr << "Error loading sprite sheet: " << path << std::endl;
    return nullptr;
  }

  // Cache the sprite sheet and return raw pointer.
  SpriteSheetRenderer* raw_ptr = renderer.get();
  sprite_sheet_cache_[key] = std::move(renderer);

#if defined(DEBUG_MODE)
  std::cout << "Loaded sprite sheet from file: " << path << std::endl;
#endif

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

#if defined(DEBUG_MODE)
  std::cout << "Resource cache cleared" << std::endl;
#endif
}

ResourceManager::~ResourceManager() {
  Clear();
}
