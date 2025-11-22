#include <unordered_map>
#include "../entity/Entity.h"

struct Collider {
    float w, h;
};

std::unordered_map<Entity,Collider> colliders;

void addCollider(Entity e, float w, float h) {
    colliders[e] = { w, h };
}