#include "Collider.h"

// Define globals
std::unordered_map<Entity, Collider> colliders;
std::vector<CollisionInfo> contacts;

// Define function
void addCollider(Entity e, float w, float h, bool isTrigger = false) {
    colliders[e] = { w, h , isTrigger};
}
