/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "Game.h"
#include <SDL2/SDL_image.h>
#include "../core/scenemanager/SceneManager.h"
#include "Scenes/SceneOne.h"
#include <iostream>

bool Game::running = true;

bool Game::init(const char* title, int width, int height, bool fs)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    gWindow = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        fs ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN
    );

    if (!gWindow) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!gRenderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return false;
    }

    // Register and switch to the first scene
    SceneOne* sceneOne = new SceneOne();
    SceneManager::addScene("SceneOne", sceneOne);
    SceneManager::switchTo("SceneOne");

    return true;
}

void Game::run()
{
    std::cout << "Game running" << std::endl;
    Uint32 prev = SDL_GetTicks();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                    SceneManager::windowFocused = true;

                if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                    SceneManager::windowFocused = false;
            }
        }

        Uint32 now = SDL_GetTicks();
        float dt = (now - prev) / 1000.0f;
        prev = now;

        if (!SceneManager::windowFocused) {
            dt = 0.0f;      
        }else{
            SceneManager::update(dt);
        }
    }
}


void Game::shutdown()
{
    SceneManager::unloadCurrent();

    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);

    SDL_Quit();
}
