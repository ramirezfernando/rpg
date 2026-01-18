#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <string>

#include "graphics/sprite_sheet_renderer.h"

// Singleton resource manager for loading and caching assets (textures, sprite
// sheets, etc.). Prevents duplicate loads and provides centralized cleanup.
class ResourceManager {
 public:
  static ResourceManager& GetInstance();

  // Delete copy constructor and assignment operator to enforce singleton.
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  // Load or retrieve a cached texture.
  SDL_Texture* GetTexture(const char* file_name);

  // Load or retrieve a cached sprite sheet renderer.
  SpriteSheetRenderer* GetSpriteSheet(const char* path, int sprite_width,
                                      int sprite_height, int margin = 0,
                                      int spacing = 0);

  // Clear all cached resources (called on shutdown).
  void Clear();

  // Destructor handles cleanup.
  ~ResourceManager();

 private:
  ResourceManager() = default;

  // Texture cache: filename -> SDL_Texture*
  std::map<std::string, SDL_Texture*> texture_cache_;

  // Sprite sheet cache: path -> unique_ptr<SpriteSheetRenderer>
  std::map<std::string, std::unique_ptr<SpriteSheetRenderer>>
      sprite_sheet_cache_;
};
