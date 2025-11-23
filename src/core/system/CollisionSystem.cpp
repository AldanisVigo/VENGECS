// #include "CollisionSystem.h"
// #include <algorithm>
// #include <iostream>

// void collisionSystem(float dt) {
//     const int ITERATIONS = 5;
//     float stepDt = dt / ITERATIONS;

//     contacts.clear();

//     for (int step = 0; step < ITERATIONS; ++step) {
//         for (auto& [aEntity, aBody] : rigidbodies) {
//             if (!transforms.count(aEntity) || !colliders.count(aEntity)) continue;

//             Transform& aTr = transforms[aEntity];
//             Collider& aCol = colliders[aEntity];

//             float nextX = aTr.x + aBody.velocity.dx * stepDt;
//             float nextY = aTr.y + aBody.velocity.dy * stepDt;

//             for (auto& [bEntity, bBody] : rigidbodies) {
//                 if (aEntity == bEntity) continue;
//                 if (!transforms.count(bEntity) || !colliders.count(bEntity)) continue;

//                 Transform& bTr = transforms[bEntity];
//                 Collider& bCol = colliders[bEntity];

//                 float overlapX = std::min(nextX + aCol.w, bTr.x + bCol.w) - std::max(nextX, bTr.x);
//                 float overlapY = std::min(nextY + aCol.h, bTr.y + bCol.h) - std::max(nextY, bTr.y);

//                 if (overlapX > 0 && overlapY > 0) {
//                     contacts.push_back({aEntity, bEntity});

//                     if (aCol.isTrigger || bCol.isTrigger) continue;

//                     float totalMass = aBody.mass.mass + bBody.mass.mass;
//                     if (totalMass <= 0) totalMass = 1.0f;

//                     if (overlapX < overlapY) {
//                         float push = overlapX * (bBody.mass.mass / totalMass) * (aBody.velocity.dx > 0 ? -1 : 1);
//                         nextX += push;
//                         bTr.x -= overlapX * (aBody.mass.mass / totalMass) * (aBody.velocity.dx > 0 ? -1 : 1);
//                         aBody.velocity.dx = 0;
//                     } else {
//                         float push = overlapY * (bBody.mass.mass / totalMass) * (aBody.velocity.dy > 0 ? -1 : 1);
//                         nextY += push;
//                         bTr.y -= overlapY * (aBody.mass.mass / totalMass) * (aBody.velocity.dy > 0 ? -1 : 1);
//                         aBody.velocity.dy = 0;
//                     }
//                 }
//             }

//             aTr.x = nextX;
//             aTr.y = nextY;
//         }
//     }
// }

#include "CollisionSystem.h"
#include <algorithm>
#include <iostream>

void collisionSystem(float dt) {
    const int ITERATIONS = 5;
    float stepDt = dt / ITERATIONS;

    contacts.clear(); // reset contacts each frame

    for (int step = 0; step < ITERATIONS; ++step) {
        // Iterate over all colliders, not just rigidbodies
        for (auto& [aEntity, aCol] : colliders) {
            // Skip if no transform (cannot calculate position)
            if (!transforms.count(aEntity)) continue;
            Transform& aTr = transforms[aEntity];

            Rigidbody* aBody = rigidbodies.count(aEntity) ? &rigidbodies[aEntity] : nullptr;

            // Calculate tentative next position (rigidbodies only)
            float nextX = aTr.x + (aBody ? aBody->velocity.dx * stepDt : 0);
            float nextY = aTr.y + (aBody ? aBody->velocity.dy * stepDt : 0);

            for (auto& [bEntity, bCol] : colliders) {
                if (aEntity == bEntity) continue;
                if (!transforms.count(bEntity)) continue;

                Transform& bTr = transforms[bEntity];
                Rigidbody* bBody = rigidbodies.count(bEntity) ? &rigidbodies[bEntity] : nullptr;

                // Calculate overlaps
                float overlapX = std::min(nextX + aCol.w, bTr.x + bCol.w) - std::max(nextX, bTr.x);
                float overlapY = std::min(nextY + aCol.h, bTr.y + bCol.h) - std::max(nextY, bTr.y);

                if (overlapX > 0 && overlapY > 0) {
                    // Collision detected
                    contacts.push_back({aEntity, bEntity});

                    // Skip resolution if either is a trigger
                    if (aCol.isTrigger || bCol.isTrigger) continue;

                    // Only resolve if at least one has a Rigidbody
                    if (!aBody && !bBody) continue;

                    float massA = aBody ? aBody->mass.mass : 0.0f;
                    float massB = bBody ? bBody->mass.mass : 0.0f;
                    float totalMass = massA + massB;
                    if (totalMass <= 0) totalMass = 1.0f;

                    if (overlapX < overlapY) {
                        // Resolve X axis
                        float pushA = overlapX * (massB / totalMass) * (aBody && aBody->velocity.dx > 0 ? -1 : 1);
                        float pushB = overlapX * (massA / totalMass) * (bBody && bBody->velocity.dx > 0 ? -1 : 1);

                        if (aBody) nextX += pushA;
                        if (bBody) bTr.x -= pushB;

                        if (aBody) aBody->velocity.dx = 0;
                    } else {
                        // Resolve Y axis
                        float pushA = overlapY * (massB / totalMass) * (aBody && aBody->velocity.dy > 0 ? -1 : 1);
                        float pushB = overlapY * (massA / totalMass) * (bBody && bBody->velocity.dy > 0 ? -1 : 1);

                        if (aBody) nextY += pushA;
                        if (bBody) bTr.y -= pushB;

                        if (aBody) aBody->velocity.dy = 0;
                    }
                }
            }

            // Apply position update if entity has Rigidbody
            if (aBody) {
                aTr.x = nextX;
                aTr.y = nextY;
            }
        }
    }
}
