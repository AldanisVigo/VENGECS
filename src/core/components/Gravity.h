/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include "../entity/Entity.h"
#include <unordered_map>

// --- Gravity Component ---
struct Gravity {
    float force; // positive force pulls downwards
};

// ECS storage
std::unordered_map<Entity, Gravity> gravities;

// --- Add Gravity to an Entity ---
void addGravity(Entity e, float force = 9.8f) {
    gravities[e] = { force };
}

