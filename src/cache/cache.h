#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <expected>
#include <map>
#include <memory>
#include <string>

#include "graphics/renderer.h"
#include "graphics/sprite.h"

// Lazily-initialized Meyer's Singleton class for caching textures and sprites.
class Cache {
 public:
  static Cache* GetInstance();

  ~Cache();
  Cache(const Cache&) = delete;
  Cache& operator=(const Cache&) = delete;
  Cache(Cache&&) = delete;
  Cache& operator=(Cache&&) = delete;

  std::expected<SDL_Texture*, std::string> GetOrCreateTexture(
      const char* file_name);
  std::expected<const Sprite*, std::string> GetOrCreateSpriteSheet(
      const char* file_path, Sprite::Dimension dimension);

 private:
  Cache() = default;
  static std::expected<SDL_Texture*, std::string> CreateTexture(
      const char* file_name);

  // Texture cache: file_name -> SDL_Texture*
  std::map<std::string, SDL_Texture*> texture_cache_;
  // Sprite sheet cache: file_path -> unique_ptr<Sprite>
  std::map<std::string, std::unique_ptr<Sprite>> sprite_sheet_cache_;
};