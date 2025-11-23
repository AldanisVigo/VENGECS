/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

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
#include "../../core/audio/AudioManager.h"
#include "../../core/components/Collider.h"

void loadBackgroundMusicAndSFX(){
    AudioManager::loadMusic("bgm", "../assets/background.mp3");
    AudioManager::playMusic("bgm");
    AudioManager::loadSFX("jump", "../assets/boom.mp3");
}

void generatePlayer(Entity* player) {
    

    std::unordered_map<std::string, Animation> playerAnims = {
        {"walk",   {0, 4, 0.2f, 0.0f}},
        {"attack", {4, 7, 0.2f, 0.0f}},
        {"idle", {10,3, 0.2f, 0.0f}}
    };

    // Player
    addTransform(*player, 210.0f, 50.0f);
    addSprite(*player,
              loadTexture("../assets/sprite.png"),
              18.0f, 35.0f,
              playerAnims,
              "idle",
              false);

    addCollider(*player,   18.0f, 35.0f, false);
    addRigidbody(*player,  20.0, 0, 100.0f);
    addGravity(*player,    50.0);
    addInput(*player, SDL_SCANCODE_A, SDL_SCANCODE_D,
                     SDL_SCANCODE_W, SDL_SCANCODE_S,
                     SDL_SCANCODE_SPACE,SDL_SCANCODE_ESCAPE,
                     SDL_SCANCODE_RETURN,  20.0f);
}

void generatePlatformOne(Entity* platformOne){
    // Platform One
    addTransform(*platformOne, 200.0f, 200.0f);
    addSprite(*platformOne, loadTexture("../assets/platform.png"),
              100.0f, 30.0f,
              { {"idle", { 
                    0,      // startFrame
                    1,      // numFrames
                    0.0f,
                    0.0f
               }}},
              "idle", false);

    addCollider(*platformOne, 100.0f, 30.0f, false);
    addRigidbody(*platformOne, 0.0f, 0.0f, 3000000.0f);

}

void generatePlatformTwo(Entity* platformTwo){
    // Platform Two
    addTransform(*platformTwo, 50.0f, 140.0f);
    addSprite(*platformTwo, loadTexture("../assets/platform.png"),
              100.0f, 30.0f,
              { {"idle", { 
                    0,      // startFrame
                    1,      // numFrames
                    0.0f,
                    0.0f
              }}},
              "idle", false);

    addCollider(*platformTwo, 100.0f, 30.0f, false);
    addRigidbody(*platformTwo, 0.0f, 0.0f, 3000000.0f);
}

void generateBushes(Entity* bushOne, Entity* bushTwo, Entity* platformTwo, Entity* platformOne){
    // Add an animated bush to the scene
    std::unordered_map<std::string, Animation> bushAnims = {
        {"sway",   {0, 2, 0.2f, 0.0f}},
    };
    float bushX = transforms[*platformTwo].x + (sprites[*platformTwo].width - 25.0f) / 2; // center bush
    float bushY = transforms[*platformTwo].y - 28.0f - 1; // top of bush sits on top of platform
    addTransform(*bushOne, bushX, bushY);
    addSprite(*bushOne, loadTexture("../assets/bush.png"), 25.0f, 28.0f, bushAnims, "sway", false);
    addCollider(*bushOne, 25.0f, 28.0f, true);


    // Add another animated bush to the scene
    bushX = transforms[*platformOne].x + (sprites[*platformOne].width - 25.0f) / 2; // center bush
    bushY = transforms[*platformOne].y - 28.0f - 1; // top of bush sits on top of platform
    addTransform(*bushTwo, bushX, bushY);
    addSprite(*bushTwo, loadTexture("../assets/bush.png"), 25.0f, 28.0f, bushAnims, "sway", false);
    addCollider(*bushTwo, 25.0f, 28.0f, true);
}

void generateInitParticles(Entity* particleEmitter, Entity* player){
    // Create a particle entity
    addTransform(*particleEmitter, transforms[*player].x, transforms[*player].y);
    addParticleSystem(
        *particleEmitter,
        1000,              // 50 particles
        CircularSpread,    
        1.0f,              // min lifetime (seconds)
        1000000.0f,        // max lifetime
        true,              // follow gravity
        0.0f, 50.0f,       // gravity X/Y (smaller)
        2.0f, 2.0f         // noise X/Y (smaller)
    );
}


void SceneOne::onLoad() {
    // Initialize entities
    player       = createEntity();
    platformOne  = createEntity();
    platformTwo  = createEntity();
    bushOne = createEntity();
    bushTwo = createEntity();
    particleEmitter = createEntity();


    loadBackgroundMusicAndSFX();
    generatePlayer(&player);
    generatePlatformOne(&platformOne);
    generatePlatformTwo(&platformTwo);
    generateBushes(&bushOne,&bushTwo,&platformTwo,&platformOne);
    generateInitParticles(&particleEmitter,&player);
}

void SceneOne::onUpdate(float dt) {
    if (!SceneManager::windowFocused) {
        renderSystem();
        return;
    }

    inputSystem(dt);
    spriteAnimationSystem(dt);
    gravitySystem(dt);
    movementSystem(dt);      
    collisionSystem(dt);     
    particleSystemUpdate(dt);  

    // Check for contacts
    for (auto& c : contacts) {
        
        // Check for contact with tree trigger
        if (c.a == this->bushOne || c.b == this->bushOne) {
            std::cout << "Touching bush one.\n";
            sprites[bushOne].flipH = true;
            break;
        }else if(c.a == this->bushTwo || c.b == this->bushTwo){
            std::cout << "Touching bush two.\n";
            sprites[bushTwo].flipH = true;
        }else{
            std::cout << "Not touching any bushes.\n";
            sprites[bushOne].flipH = false;
            sprites[bushTwo].flipH = false;
        }
    }

    renderSystem();
}