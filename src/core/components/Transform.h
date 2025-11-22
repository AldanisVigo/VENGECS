#pragma once
#include <unordered_map>
#include "../entity/Entity.h"

struct Transform {
    float x, y;
};

std::unordered_map<Entity, Transform> transforms;

void addTransform(Entity e, float x, float y) {
    transforms[e] = { x, y };
}