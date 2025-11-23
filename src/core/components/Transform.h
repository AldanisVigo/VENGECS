#pragma once
#include <unordered_map>
#include "../entity/Entity.h"

struct Transform {
    float x, y;
};

// Declare the global variable
extern std::unordered_map<Entity, Transform> transforms;

// Declare the function
void addTransform(Entity e, float x, float y);
