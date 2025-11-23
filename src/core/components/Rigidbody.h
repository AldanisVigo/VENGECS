/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

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

extern std::unordered_map<Entity, Rigidbody> rigidbodies;


extern void addRigidbody(Entity e, float dx, float dy, float mass);