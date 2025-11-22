#pragma once
#include "../components/Transform.h"
#include "../components/Sprite.h"
#include "../entity/Entity.h"
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Global ECS maps
extern std::unordered_map<Entity, Transform> transforms;
extern std::unordered_map<Entity, Sprite> sprites;

// SDL objects
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

void renderSystem() {
    if (!gRenderer) return;

    // Clear screen (black)
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    // Draw all sprites
    for (auto& [entity, sprite] : sprites) {
        auto it = transforms.find(entity);
        if (it == transforms.end()) continue;

        Transform& t = it->second;

        SDL_Rect dstRect;
        dstRect.x = static_cast<int>(t.x);
        dstRect.y = static_cast<int>(t.y);
        dstRect.w = sprite.width;
        dstRect.h = sprite.height;

        SDL_Rect srcRect;
        srcRect.x = sprite.curFrame * sprite.width;
        srcRect.y = 0;
        srcRect.w = sprite.width;
        srcRect.h = sprite.height;

        // Choose flip
        SDL_RendererFlip flip = sprite.flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(gRenderer, sprite.tex, &srcRect, &dstRect, 0.0, nullptr, flip);
    }

    // Present frame
    SDL_RenderPresent(gRenderer);
}
