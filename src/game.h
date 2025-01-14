#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

#pragma once

#ifndef GAME_H
#define GAME_H
class Game {
public: 
  void Init(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen);
  void HandleEvents();
  void Update();
  void Render(); 
  void Clean();
  void SetIsRunning(bool is_running);
  bool GetIsRunning();
  static SDL_Renderer* renderer_;
  static SDL_Event event_; 
private:
  bool is_running_;
  SDL_Window *window_;
};

#endif