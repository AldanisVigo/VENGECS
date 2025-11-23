/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "ParticleSys.h"
#include "../components/Transform.h" // so we can offset particles by emitter position
#include <cstdlib>
#include <cmath>

std::unordered_map<Entity, ParticleSys> particleSystems;

void addParticleSystem(Entity e, int particleCount, ParticleSystemShape shape,
                       float lifetimeMin, float lifetimeMax,
                       bool followGravity,
                       float gravityX, float gravityY,
                       float noiseX, float noiseY)
{
    ParticleSys sys;
    sys.shape = shape;
    sys.particleLifetimeMin = lifetimeMin;
    sys.particleLifetimeMax = lifetimeMax;
    sys.particlesFollowGravity = followGravity;
    sys.gravityX = gravityX;
    sys.gravityY = gravityY;
    sys.noiseX = noiseX;
    sys.noiseY = noiseY;

    sys.particles.reserve(particleCount);

    // Get emitter position if it has a transform
    float emitterX = 0.0f;
    float emitterY = 0.0f;
    if (transforms.count(e)) {
        emitterX = transforms[e].x;
        emitterY = transforms[e].y;
    }

    for (int i = 0; i < particleCount; i++) {
        Particle p;
        p.x = 0;
        p.y = 0;
        p.scale = 1.0f;
        p.opacity = 1.0f;

        // Give a longer lifetime so we can see the particles
        p.lifetime = lifetimeMin + static_cast<float>(rand()) / RAND_MAX * (lifetimeMax - lifetimeMin);

        if (shape == CircularSpread) {
            float angle = static_cast<float>(rand()) / RAND_MAX * 6.283185f; // 0..2pi
            float speed = 50.0f + static_cast<float>(rand()) / RAND_MAX * 150.0f;
            p.vx = cos(angle) * speed;
            p.vy = sin(angle) * speed;
        } else { // Linear
            p.vx = 0.0f;
            p.vy = 0.0f;
        }

        sys.particles.push_back(p);
    }

    particleSystems[e] = sys;
}
