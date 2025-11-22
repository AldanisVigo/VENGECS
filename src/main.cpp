#include "core/util/sdl_init.h"
#include "core/scenemanager/SceneManager.h"
#include "Game/Scenes/SceneOne.h"

int main() {
    if (!initSDL("VENGecs", 800, 600))
        return 1;

    // Create a SceneOne instance
    SceneOne* sceneOne = new SceneOne();

    // Register the scene with the SceneManager
    SceneManager::addScene("game", sceneOne);

    // Start with the "game" scene
    SceneManager::switchTo("game");

    bool running = true;
    Uint32 prev = SDL_GetTicks();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = false;

        Uint32 now = SDL_GetTicks();
        float dt = (now - prev) / 1000.0f;
        prev = now;

        // Update the current scene
        SceneManager::update(dt);
    }

    shutdownSDL();
    return 0;
}
