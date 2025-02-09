#include "background.h"
#include "constants/game_constants.h"
#include "util.h"

Background::Background(const char* file_path) {
  background_texture_ = Util::LoadTexture(file_path);
}

Background::~Background() {
  SDL_DestroyTexture(background_texture_);
  std::cout << "Background destroyed" << std::endl;
}

void Background::Update() {
  src_rect_.w = Constants::WINDOW_SIZE;
  src_rect_.h = Constants::WINDOW_SIZE;
  src_rect_.x = 0;
  src_rect_.y = 0;
  dest_rect_.h = src_rect_.h;
  dest_rect_.w = src_rect_.w;
  dest_rect_.x = x_pos_;
  dest_rect_.y = y_pos_;
}

void Background::Render() {
  SDL_RenderCopy(Game::renderer_, background_texture_, &src_rect_, &dest_rect_);
}