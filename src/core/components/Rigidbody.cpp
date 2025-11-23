#include "Rigidbody.h"

std::unordered_map<Entity, Rigidbody> rigidbodies;

void addRigidbody(Entity e, float dx, float dy, float mass) {
    rigidbodies[e] = {{dx,dy},mass};
}