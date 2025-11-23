#include "../entity/Entity.h"
#include "../components/Rigidbody.h"
#include "../components/Gravity.h"
#include <iostream>

void gravitySystem(float dt) {
    // std::cout << "[Gravity] dt=" << dt << " entities=" << gravities.size() << "\n";

    for (auto& [entity, gravity] : gravities) {
        // Only apply gravity if entity has velocity
        if (rigidbodies.find(entity) != rigidbodies.end()) {
            Rigidbody& body = rigidbodies[entity];
            body.velocity.dy += gravity.force * dt;
        }
    }
}
