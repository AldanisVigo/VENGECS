/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include <unordered_map>
#include "../components/Sprite.h"

void spriteAnimationSystem(float dt) {
    for (auto& [entity, sprite] : sprites) {
        if (!sprite.animations.count(sprite.currentAnim)) continue;
        Animation& anim = sprite.animations[sprite.currentAnim];

        anim.tickCounter -= dt;
        if (anim.tickCounter <= 0.0f) {
            anim.tickCounter += anim.frameDelay;

            // Advance frame within the animation range
            sprite.curFrame++;
            if (sprite.curFrame >= anim.startFrame + anim.numFrames) {
                sprite.curFrame = anim.startFrame; // loop animation
            }
        }
    }
}
