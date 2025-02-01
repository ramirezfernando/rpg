#include "character.h"
#include "util.h"

void Character::Update() {
  src_rect_.w = 64;
  src_rect_.h = 64;
  src_rect_.x = 0;
  src_rect_.y = 0;
  dest_rect_.x = x_pos_;
  dest_rect_.y = y_pos_;
  dest_rect_.h = src_rect_.h * 2;
  dest_rect_.w = src_rect_.w * 2;

  std::string filename = file_path_ + to_string(0) + ".png";
  const char* file = filename.c_str();
  character_texture_ = Util::LoadTexture(file);
  /*
  // Handles character animation
  if (count_ < frames_) {
    std::string filename = file_path_ + to_string(count_) + ".png";
    const char* file = filename.c_str();
    character_texture_ = Util::LoadTexture(file);
    SDL_Delay(delay_);
    count_++;
  } else {
    count_ = 0;
  }
  */
}

void Character::Render() {
  SDL_RenderCopy(Game::renderer_, character_texture_, &src_rect_, &dest_rect_);
}

void Character::Clean() {
  SDL_DestroyTexture(character_texture_);
}