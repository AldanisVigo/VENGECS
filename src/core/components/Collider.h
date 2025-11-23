/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/
#pragma once
#include <unordered_map>
#include "../entity/Entity.h"
#include <vector>

struct Collider {
    float w, h;
    bool isTrigger = false;
};

extern std::unordered_map<Entity,Collider> colliders;

extern void addCollider(Entity e, float w, float h, bool isTrigger);

// Global contacts vector (cleared each frame)
struct CollisionInfo { Entity a, b; };
extern std::vector<CollisionInfo> contacts;