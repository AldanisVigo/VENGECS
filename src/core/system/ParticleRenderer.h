/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include "../components/ParticleSys.h"
#include "../util/TextureLoader.h"
#include <SDL2/SDL.h>
#include <unordered_map>

// Global particle texture
extern SDL_Texture* gParticleTex;

// Load particle texture (call once in onLoad or Game init)
SDL_Texture* loadParticleTexture();

// Render system for particles
void particleRenderSystem();
