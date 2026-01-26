#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <string>

#include "graphics/sprite.h"

// Lazily-initialized Meyer's Singleton class for caching textures and sprites.
class Cache {
 public:
  static Cache* GetInstance();

  ~Cache();
  Cache(const Cache&) = delete;             // Copy constructor.
  Cache(Cache&&) = delete;                  // Move constructor.
  Cache& operator=(const Cache&) = delete;  // Copy assignment operator.
  Cache& operator=(Cache&&) = delete;       // Move assignment operator.

  SDL_Texture* GetOrCreateTexture(const char* file_name);
  Sprite* GetOrCreateSprite(const char* file_path, int sprite_width, int sprite_height);
  void Clear();

 private:
  Cache() = default;

  // Texture cache: file_name -> SDL_Texture*
  std::map<std::string, SDL_Texture*> texture_cache_;
  // Sprite sheet cache: file_path -> unique_ptr<Sprite>
  std::map<std::string, std::unique_ptr<Sprite>> sprite_sheet_cache_;
};