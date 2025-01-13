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
class Game
{
public: 
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); // initialize window to display the game
    void HandleEvents();
    void Update();
    void Render(); 
    void Clean(); // destroys SDL_Window
    bool Running(); // game loop variable
    void SetRunning(bool run); // set game loop variable
    static SDL_Renderer* renderer; // static renderer without the need of having multiple renderers
    static SDL_Event event; 
private:
    bool isRunning;
    SDL_Window *window;
};

#endif