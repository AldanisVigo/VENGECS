#pragma once
#include <SDL2/SDL.h>

class Game {
public:
    static bool running;
    static bool init(const char* title, int width, int height);
    static void run();
    static void shutdown();
};
