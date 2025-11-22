#include "../components/Input.h"
#include "../components/Rigidbody.h"
#include "../components/Sprite.h"
#include "../components/Gravity.h"

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
                body.velocity.dy = -40.0f;  // set upward impulse
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
