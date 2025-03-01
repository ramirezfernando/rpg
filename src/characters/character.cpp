#include "character.h"
#include <cstdlib>  // For abs()
#include "constants/game_constants.h"
#include "utils/util.h"

Character::~Character() {
  SDL_DestroyTexture(character_texture_);
  std::cout << "Character destroyed" << std::endl;
}

void Character::Update(Enemy* enemy) {
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
    Attack(enemy);
  }
}

void Character::Render() {
  SDL_RenderCopy(Game::renderer_, character_texture_, &src_rect_, &dest_rect_);
}

void Character::SetXPos(int x_pos) {
  if (IsWithinWindowBounds(x_pos, y_pos_)) {
    x_pos_ = x_pos;
  }
}

void Character::SetYPos(int y_pos) {
  if (IsWithinWindowBounds(x_pos_, y_pos)) {
    y_pos_ = y_pos;
  }
}

void Character::Attack(Enemy* enemy) {
  Uint32 current_time = SDL_GetTicks();
  if (ShouldUpdateTexture(current_time)) {
    if (ShouldIncrementTexture()) {
      std::string filename = folder_path_ + std::to_string(count_) + ".png";
      const char* file = filename.c_str();
      character_texture_ = Util::LoadTexture(file);
      count_++;
    } else {
      count_ = 0;
      should_attack_ = false;
      if (IsWithinAttackRange(enemy->GetXPos(), enemy->GetYPos())) {
        enemy->SetHealth(enemy->GetHealth() - 10);
        std::cout << "Enemy health: " << enemy->GetHealth() << std::endl;
        if (enemy->GetHealth() <= 0) {
          // TODO: Implement game over logic
        }
      }
    }
    last_frame_time_ = current_time;
  }
}

bool Character::IsWithinWindowBounds(int x_pos, int y_pos) {
  return x_pos >= 0 && x_pos <= Constants::WINDOW_SIZE - dest_rect_.w &&
         y_pos >= 0 && y_pos <= Constants::WINDOW_SIZE - dest_rect_.h;
}

bool Character::IsWithinAttackRange(int enemy_x_pos, int enemy_y_pos) {
  return abs(x_pos_ - enemy_x_pos) <= Constants::ATTACK_RANGE &&
         abs(y_pos_ - enemy_y_pos) <= Constants::ATTACK_RANGE;
}

// Adds a delay between each frame of the attack animation
bool Character::ShouldUpdateTexture(Uint32 current_time) {
  return current_time > last_frame_time_ + delay_;
}

bool Character::ShouldIncrementTexture() {
  return count_ < frames_;
}