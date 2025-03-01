#include "character.h"
#include "constants/game_constants.h"
#include "util.h"

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

  if (should_attack_) {
    Attack();
  }
}

void Character::Render() {
  SDL_RenderCopy(Game::renderer_, character_texture_, &src_rect_, &dest_rect_);
}

void Character::SetXPos(int x_pos) {
  if (IsWithinBounds(x_pos, y_pos_)) {
    x_pos_ = x_pos;
  }
}

void Character::SetYPos(int y_pos) {
  if (IsWithinBounds(x_pos_, y_pos)) {
    y_pos_ = y_pos;
  }
}

bool Character::IsWithinBounds(int x_pos, int y_pos) {
  return x_pos >= 0 && x_pos <= Constants::WINDOW_SIZE - dest_rect_.w &&
         y_pos >= 0 && y_pos <= Constants::WINDOW_SIZE - dest_rect_.h;
}

void Character::Attack() {
  Uint32 current_time = SDL_GetTicks();
  if (current_time > last_frame_time_ + delay_) {
    if (count_ < frames_) {
      std::string filename = folder_path_ + std::to_string(count_) + ".png";
      const char* file = filename.c_str();
      character_texture_ = Util::LoadTexture(file);
      count_++;
    } else {
      count_ = 0;
      should_attack_ = false;
    }
    last_frame_time_ = current_time;
  }
}