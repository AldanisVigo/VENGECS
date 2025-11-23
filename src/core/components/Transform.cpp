/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "Transform.h"

// Define the global variable
std::unordered_map<Entity, Transform> transforms;

// Define the function
void addTransform(Entity e, float x, float y) {
    transforms[e] = { x, y };
}
