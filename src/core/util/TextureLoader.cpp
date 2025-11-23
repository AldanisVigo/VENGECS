/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "TextureLoader.h"
#include "Globals.h"   // gives gRenderer
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* texture = IMG_LoadTexture(gRenderer, path.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << path
                  << " Error: " << IMG_GetError() << "\n";
    }
    return texture;
}
