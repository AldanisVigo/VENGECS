/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "ParticleRenderer.h"
#include "../util/Globals.h"
#include "../components/Transform.h"  // so we can get the entity position
#include <iostream>

SDL_Texture* gParticleTex = nullptr;

SDL_Texture* loadParticleTexture() {
    std::cout << "Loading particle texture." << std::endl;
    if (gParticleTex) return gParticleTex; // already loaded
    gParticleTex = IMG_LoadTexture(gRenderer, "../assets/particle.png");
    if (!gParticleTex) {
        std::cerr << "Failed to load particle texture: " << IMG_GetError() << "\n";
    }
    return gParticleTex;
}

void particleRenderSystem() {
    if (!gParticleTex) return;
    // std::cout << "Rendering particle system" << std::endl;

    for (auto& [entity, sys] : particleSystems) {
        if (!sys.alive) continue;

        float baseX = 0.0f;
        float baseY = 0.0f;

        // If the entity has a Transform, offset particles by it
        if (transforms.count(entity)) {
            auto& t = transforms[entity];
            baseX = t.x;
            baseY = t.y;
        }

        for (auto& p : sys.particles) {
            if (p.lifetime <= 0.0f) continue;

            SDL_Rect dst;
            dst.x = static_cast<int>(p.x + baseX);
            dst.y = static_cast<int>(p.y + baseY);

            // std::cout << "Particle: " << dst.x << ", " << dst.y << ", lifetime: " << p.lifetime << "\n";

            int texW, texH;
            SDL_QueryTexture(gParticleTex, nullptr, nullptr, &texW, &texH);
            dst.w = static_cast<int>(texW * p.scale);
            dst.h = static_cast<int>(texH * p.scale);

            SDL_SetTextureAlphaMod(gParticleTex, static_cast<Uint8>(p.opacity * 255));
            SDL_RenderCopy(gRenderer, gParticleTex, nullptr, &dst);
        }
    }
}
