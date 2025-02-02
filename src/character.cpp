#include "character.h"
#include "constants/game_constants.h"
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

  if (should_attack_) {
    Attack();
  }
}

void Character::Render() {
  SDL_RenderCopy(Game::renderer_, character_texture_, &src_rect_, &dest_rect_);
}

void Character::Clean() {
  SDL_DestroyTexture(character_texture_);
}

void Character::SetFilePath(const char* file_path) {
  file_path_ = file_path;
}

void Character::setShouldAttack(bool should_attack) {
  should_attack_ = should_attack;
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

int Character::GetXPos() {
  return x_pos_;
}

int Character::GetYPos() {
  return y_pos_;
}

bool Character::IsWithinBounds(int x_pos, int y_pos) {
  return x_pos >= 0 && x_pos <= Constants::WINDOW_SIZE - dest_rect_.w &&
         y_pos >= 0 && y_pos <= Constants::WINDOW_SIZE - dest_rect_.h;
}

void Character::Attack() {
  if (count_ < frames_) {
    std::string filename = file_path_ + std::to_string(count_) + ".png";
    const char* file = filename.c_str();
    character_texture_ = Util::LoadTexture(file);
    SDL_Delay(delay_);
    count_++;
  } else {
    count_ = 0;
    // Ensures that the character does not keep attacking
    should_attack_ = false;
  }
}