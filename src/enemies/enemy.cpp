#include "enemy.h"
#include "constants/game_constants.h"
#include "util.h"

Enemy::~Enemy() {
  SDL_DestroyTexture(enemy_texture_);
  std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::Update(int character_x_pos, int character_y_pos) {
  src_rect_.w = 96;
  src_rect_.h = 96;
  src_rect_.x = 0;
  src_rect_.y = 0;
  dest_rect_.x = x_pos_;
  dest_rect_.y = y_pos_;
  dest_rect_.h = src_rect_.h * 2;
  dest_rect_.w = src_rect_.w * 2;

  // Load the first image: 0.png
  std::string filename = folder_path_ + std::to_string(0) + ".png";
  const char* file = filename.c_str();
  enemy_texture_ = Util::LoadTexture(file);

  if (character_x_pos != x_pos_ || character_y_pos != y_pos_) {
    SDL_Delay(delay_);
    FollowCharacter(character_x_pos, character_y_pos);
  }
}

void Enemy::Render() {
  SDL_RenderCopy(Game::renderer_, enemy_texture_, &src_rect_, &dest_rect_);
}

void Enemy::FollowCharacter(int character_x_pos, int character_y_pos) {
  if (character_x_pos > x_pos_) {
    x_pos_ += Constants::ENEMY_MOVEMENT_GAP;
    folder_path_ = Constants::ENEMY_GHOST_RIGHT_FOLDER_PATH;
  } else if (character_x_pos < x_pos_) {
    x_pos_ -= Constants::ENEMY_MOVEMENT_GAP;
    folder_path_ = Constants::ENEMY_GHOST_LEFT_FOLDER_PATH;
  } 

  if (character_y_pos > y_pos_) {
    y_pos_ += Constants::ENEMY_MOVEMENT_GAP;
    folder_path_ = Constants::ENEMY_GHOST_DOWN_FOLDER_PATH;
  } else if (character_y_pos < y_pos_) {
    y_pos_ -= Constants::ENEMY_MOVEMENT_GAP;
    folder_path_ = Constants::ENEMY_GHOST_UP_FOLDER_PATH;
  }
}
