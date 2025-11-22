#pragma once
#include "SDL2/SDL.h"
#include "../entity/Entity.h"

struct Input {
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode up;
    SDL_Scancode down;
    SDL_Scancode jump;
    float movementSpeed;
};

inline std::unordered_map<Entity, Input> inputs;

inline void addInput(Entity entity, SDL_Scancode left, SDL_Scancode right, SDL_Scancode up, SDL_Scancode down, SDL_Scancode jump, float movementSpeed) {
    inputs[entity] = { left, right, up, down, jump, movementSpeed };
}