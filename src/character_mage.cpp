#include "character_mage.h"
#include "util.h"

Mage::Mage(const char* folder_path, int x_pos, int y_pos) {
  folder_path_ = folder_path;
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  frames_ = 3;
  delay_ = 70;
  count_ = 0;
}

void Mage::Attack() {
  // TODO: Implement projectile animation
  if (count_ < frames_) {
    std::string filename = folder_path_ + std::to_string(count_) + ".png";
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