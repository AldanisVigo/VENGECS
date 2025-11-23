/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include "../entity/Entity.h"
#include "../components/Rigidbody.h"
#include "../components/Transform.h"
#include "../components/Collider.h"
#include <algorithm>
#include <unordered_map>

void collisionSystem(float dt) {
    const int ITERATIONS = 5; // Subdivide movement into smaller steps for stability
    float stepDt = dt / ITERATIONS;

    for (int step = 0; step < ITERATIONS; ++step) {
        for (auto& [aEntity, aBody] : rigidbodies) {
            if (!transforms.count(aEntity) || !colliders.count(aEntity)) continue;

            Transform& aTr = transforms[aEntity];
            Collider& aCol = colliders[aEntity];

            float nextX = aTr.x + aBody.velocity.dx * stepDt;
            float nextY = aTr.y + aBody.velocity.dy * stepDt;

            for (auto& [bEntity, bBody] : rigidbodies) {
                if (aEntity == bEntity) continue;
                if (!transforms.count(bEntity) || !colliders.count(bEntity)) continue;

                Transform& bTr = transforms[bEntity];
                Collider& bCol = colliders[bEntity];

                // Calculate overlaps
                float overlapX = std::min(nextX + aCol.w, bTr.x + bCol.w) - std::max(nextX, bTr.x);
                float overlapY = std::min(nextY + aCol.h, bTr.y + bCol.h) - std::max(nextY, bTr.y);

                if (overlapX > 0 && overlapY > 0) {
                    float totalMass = aBody.mass.mass + bBody.mass.mass;
                    if (totalMass <= 0) totalMass = 1.0f;

                    // Resolve collision along the axis of least penetration
                    if (overlapX < overlapY) {
                        // Resolve X
                        float push = overlapX * (bBody.mass.mass / totalMass) * (aBody.velocity.dx > 0 ? -1 : 1);
                        nextX += push;
                        bTr.x -= overlapX * (aBody.mass.mass / totalMass) * (aBody.velocity.dx > 0 ? -1 : 1);

                        aBody.velocity.dx = 0;
                    } else {
                        // Resolve Y
                        float push = overlapY * (bBody.mass.mass / totalMass) * (aBody.velocity.dy > 0 ? -1 : 1);
                        nextY += push;
                        bTr.y -= overlapY * (aBody.mass.mass / totalMass) * (aBody.velocity.dy > 0 ? -1 : 1);

                        aBody.velocity.dy = 0;
                    }
                }
            }

            aTr.x = nextX;
            aTr.y = nextY;
        }
    }
}
