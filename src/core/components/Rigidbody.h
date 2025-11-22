#pragma once
#include <unordered_map>
#include "../entity/Entity.h"

struct Velocity {
    float dx, dy;
};

struct Mass {
    float mass;
};

struct Rigidbody {
    Velocity velocity;
    Mass mass;
};

std::unordered_map<Entity, Rigidbody> rigidbodies;


void addRigidbody(Entity e, float dx, float dy, float mass) {
    rigidbodies[e] = {{dx,dy},mass};
}