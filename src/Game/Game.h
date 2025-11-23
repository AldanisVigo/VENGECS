/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../core/scenemanager/SceneManager.h"
#include "Scenes/SceneOne.h"
#include <iostream>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

class Game {
public:
    static bool running;
    static bool init(const char* title, int width, int height,bool fs);
    static void run();
    static void shutdown();
};
