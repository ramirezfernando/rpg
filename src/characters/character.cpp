#include "character.h"
#include <cstdlib>  // For abs()
#include "constants/constants.h"
#include "util/util.h"

Character::~Character() {
  SDL_DestroyTexture(character_texture_);
  std::cout << "Character destroyed" << std::endl;
}

void Character::Update() {
  src_rect_.w = Constants::CHARACTER_SIZE;
  src_rect_.h = Constants::CHARACTER_SIZE;
  src_rect_.x = 0;
  src_rect_.y = 0;
  dest_rect_.x = x_pos_;
  dest_rect_.y = y_pos_;
  dest_rect_.h = src_rect_.h * 2;
  dest_rect_.w = src_rect_.w * 2;

  // Load the first image: 0.png
  std::string filename = folder_path_ + std::to_string(0) + ".png";
  const char* file = filename.c_str();
  character_texture_ = Util::LoadTexture(file);
}

void Character::Render() {
  SDL_RenderCopy(Game::renderer_, character_texture_, &src_rect_, &dest_rect_);
}

void Character::SetXPos(int x_pos) {
  if (IsWithinWindowBounds()) {
    x_pos_ = x_pos;
  }
}

void Character::SetYPos(int y_pos) {
  if (IsWithinWindowBounds()) {
    y_pos_ = y_pos;
  }
}

bool Character::IsWithinWindowBounds() {
  return x_pos_ >= 0 && x_pos_ <= Constants::WINDOW_SIZE - dest_rect_.w &&
         y_pos_ >= 0 && y_pos_ <= Constants::WINDOW_SIZE - dest_rect_.h;
}

bool Character::ShouldUpdateTexture(Uint32 current_time) {
  return current_time > last_frame_time_ + delay_;
}

bool Character::ShouldIncrementTexture() {
  return count_ < frames_;
}