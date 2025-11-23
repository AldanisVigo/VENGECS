#pragma once
#include "../components/ParticleSys.h"
#include <cmath>

void particleSystemUpdate(float dt) {
    for (auto& [entity, sys] : particleSystems) {
        if (!sys.alive) continue;

        for (auto& p : sys.particles) {
            if (p.lifetime <= 0.0f) continue;

            // Apply velocity
            p.x += p.vx * dt;
            p.y += p.vy * dt;

            // Apply gravity
            if (sys.particlesFollowGravity) {
                p.vx += sys.gravityX * dt;
                p.vy += sys.gravityY * dt;
            }

            // Apply noise
            float noiseX = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * sys.noiseX;
            float noiseY = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * sys.noiseY;
            p.vx += noiseX * dt;
            p.vy += noiseY * dt;

            // Reduce lifetime
            p.lifetime -= dt;

            // Fade out as lifetime ends
            p.opacity = std::fmax(0.0f, p.lifetime / sys.particleLifetimeMax);
        }
    }
}
