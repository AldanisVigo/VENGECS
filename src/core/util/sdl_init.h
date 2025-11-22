#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

bool initSDL(const char* title, int width, int height);
void shutdownSDL();
