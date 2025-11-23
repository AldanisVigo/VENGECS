/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "../components/Input.h"
#include "../components/Rigidbody.h"
#include "../components/Sprite.h"
#include "../components/Gravity.h"
#include "../audio/AudioManager.h"
#include "../components/Transform.h"
#include "../components/ParticleSys.h"

inline void inputSystem(float dt) {
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    for (auto& [entity, input] : inputs) {
        auto& body = rigidbodies[entity];

        // Reset horizontal velocity
        body.velocity.dx = 0.0f;

        bool moving = false;

        // --- Jump ---
        if (keyState[input.jump]) {
            // Only jump if touching ground (we need a 'grounded' check)
            if(gravities.count(entity) && body.velocity.dy == 0.0f) {
                // later, when player jumps
                AudioManager::playSFX("jump");
                // Create a particle entity
                Entity particleEmitter = createEntity();
                addTransform(particleEmitter, transforms[entity].x + 9.0f , transforms[entity].y + 35.0f);
                addParticleSystem(
                    particleEmitter,
                    50,           // 50 particles
                    Linear,    
                    1.0f,           // min lifetime (seconds)
                    2.0f,           // max lifetime
                    true,           // follow gravity
                    0.0f, -42.0f,   // gravity X/Y (smaller)
                    100.0f, 100.0f  // noise X/Y (smaller)
                );
                body.velocity.dy = -60.0f;  // set upward impulse
            }
        }

        // --- Horizontal movement ---
        if (keyState[input.left]){
            body.velocity.dx = -input.movementSpeed;
            sprites[entity].flipH = true;
            moving = true;
        }
        if (keyState[input.right]){
            body.velocity.dx = input.movementSpeed;
            sprites[entity].flipH = false;
            moving = true;
        }

        // --- Vertical movement (optional) ---
        if (keyState[input.up]){
            // only if free-flying, otherwise skip (gravity handles vertical)
            // body.velocity.dy = -input.movementSpeed;
            moving = true;
        }
        if (keyState[input.down]){
            // only if free-flying
            // body.velocity.dy = input.movementSpeed;
            moving = true;
        }

        // --- Set animation ---
        if (moving) {
            if(sprites[entity].currentAnim != "walk"){
                setSpriteAnimation(entity,"walk");
            }
        } else {
            if(sprites[entity].currentAnim != "attack"){
                setSpriteAnimation(entity,"attack");
            }
        }
    }
}
