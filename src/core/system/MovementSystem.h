/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include "../components/Transform.h"
#include "../components/Rigidbody.h"
#include "../entity/Entity.h"
#include <unordered_map>

void movementSystem(float dt) {
    for (auto& [entity, body] : rigidbodies) {
        if (transforms.count(entity)) {
            auto& t = transforms[entity];
            t.x += body.velocity.dx * dt;
            t.y += body.velocity.dy * dt;
        }
    }
}