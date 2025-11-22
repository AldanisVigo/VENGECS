#include "../entity/Entity.h"
#include "../components/Rigidbody.h"
#include "../components/Gravity.h"

void gravitySystem(float dt) {
    for (auto& [entity, gravity] : gravities) {
        // Only apply gravity if entity has velocity
        if (rigidbodies.find(entity) != rigidbodies.end()) {
            Rigidbody& body = rigidbodies[entity];
            body.velocity.dy += gravity.force * dt;
        }
    }
}
