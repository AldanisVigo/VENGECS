#include "SceneOne.h"
#include "../../core/scenemanager/SceneManager.h"
#include "../../core/util/TextureLoader.h"
#include "../../core/system/InputSystem.h"
#include "../../core/system/SpriteAnimatorSystem.h"
#include "../../core/system/GravitySystem.h"
#include "../../core/system/MovementSystem.h"
#include "../../core/system/CollisionSystem.h"
#include "../../core/system/RenderSystem.h"
#include "../../core/system/ParticleSystem.h"
#include "../../core/system/ParticleRenderer.h"

void SceneOne::onLoad() {
    loadParticleTexture();

    Entity player       = createEntity();
    Entity platformOne  = createEntity();
    Entity platformTwo  = createEntity();

    Animation idleAnim = { 
        0,      // startFrame
        1,      // numFrames
        0.0f,
        0.0f
    };

    std::unordered_map<std::string, Animation> playerAnims = {
        {"walk",   {0, 4, 0.2f, 0.0f}},
        {"attack", {4, 7, 0.2f, 0.0f}}
    };

    // Player
    addTransform(player, 100.0f, 50.0f);
    addSprite(player,
              loadTexture("../assets/sprite.png"),
              18.0f, 35.0f,
              playerAnims,
              "attack",
              false);

    addCollider(player,   18.0f, 35.0f);
    addRigidbody(player,  20.0, 0, 100.0f);
    addGravity(player,    20.0);
    addInput(player, SDL_SCANCODE_A, SDL_SCANCODE_D,
                     SDL_SCANCODE_W, SDL_SCANCODE_S,
                     SDL_SCANCODE_SPACE, 20.0f);

    // Platform One
    addTransform(platformOne, 200.0f, 200.0f);
    addSprite(platformOne, loadTexture("../assets/platform.png"),
              100.0f, 30.0f,
              { {"idle", idleAnim} },
              "idle", false);

    addCollider(platformOne, 100.0f, 30.0f);
    addRigidbody(platformOne, 0.0f, 0.0f, 3000000.0f);

    // Platform Two
    addTransform(platformTwo, 50.0f, 140.0f);
    addSprite(platformTwo, loadTexture("../assets/platform.png"),
              100.0f, 30.0f,
              { {"idle", idleAnim} },
              "idle", false);

    addCollider(platformTwo, 100.0f, 30.0f);
    addRigidbody(platformTwo, 0.0f, 0.0f, 3000000.0f);
    

    // Create a particle entity
    Entity particleEmitter = createEntity();
    addTransform(particleEmitter, transforms[player].x, transforms[player].y);
    addParticleSystem(
        particleEmitter,
        1000,              // 50 particles
        CircularSpread,    
        1.0f,              // min lifetime (seconds)
        1000000.0f,        // max lifetime
        true,              // follow gravity
        0.0f, 50.0f,       // gravity X/Y (smaller)
        2.0f, 2.0f         // noise X/Y (smaller)
    );
}

void SceneOne::onUpdate(float dt) {
    inputSystem(dt);
    spriteAnimationSystem(dt);
    gravitySystem(dt);
    movementSystem(dt);
    collisionSystem(dt);
    particleSystemUpdate(dt);  
    renderSystem();
}
