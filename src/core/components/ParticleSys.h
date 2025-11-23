#pragma once
#include "Particle.h"
#include "../entity/Entity.h"
#include <unordered_map>
#include <vector>
#include <random>

enum ParticleSystemShape {
    CircularSpread,
    Linear
};

struct ParticleSys {
    std::vector<Particle> particles;
    ParticleSystemShape shape;
    float particleLifetimeMin;
    float particleLifetimeMax;
    bool alive = true;
    bool particlesFollowGravity = false;
    float gravityX = 0.0f;
    float gravityY = 0.0f;
    float noiseX = 0.0f;
    float noiseY = 0.0f;
};

extern std::unordered_map<Entity, ParticleSys> particleSystems;

// Initialize a particle system
void addParticleSystem(Entity e, int particleCount, ParticleSystemShape shape,
                       float lifetimeMin, float lifetimeMax,
                       bool followGravity = false,
                       float gravityX = 0.0f, float gravityY = 0.0f,
                       float noiseX = 0.0f, float noiseY = 0.0f);
