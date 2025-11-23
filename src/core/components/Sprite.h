/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include <unordered_map>
#include <string>
#include "../entity/Entity.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

struct Animation {
    int startFrame;      // starting frame in the spritesheet
    int numFrames;       // total frames for this animation
    float frameDelay;    // seconds per frame
    float tickCounter;   // counts down to advance frame
};

struct Sprite {
    SDL_Texture* tex;
    float width, height;
    bool flipH = false;

    std::unordered_map<std::string, Animation> animations; // all animations
    std::string currentAnim; // which animation is currently playing
    int curFrame;            // current frame in current animation
};

std::unordered_map<Entity, Sprite> sprites;

// Add sprite with animations
void addSprite(Entity e, SDL_Texture* tex, float width, float height,
               const std::unordered_map<std::string, Animation>& anims,
               const std::string& startAnim, bool flipH=false)
{
    Sprite s;
    s.tex = tex;
    s.width = width;
    s.height = height;
    s.animations = anims;
    s.currentAnim = startAnim;
    s.curFrame = 0;
    s.flipH = flipH;

    if (s.animations.count(startAnim)) {
        s.animations[startAnim].tickCounter = s.animations[startAnim].frameDelay;
    }

    sprites[e] = s;
}

void setSpriteAnimation(Entity e, const std::string& animName) {
    if (!sprites.count(e)) return;
    Sprite& s = sprites[e];
    if (s.currentAnim == animName) return;
    if (!s.animations.count(animName)) return;

    s.currentAnim = animName;

    // Reset curFrame to the start frame of the new animation
    s.curFrame = s.animations[animName].startFrame;
    s.animations[animName].tickCounter = s.animations[animName].frameDelay;
}
