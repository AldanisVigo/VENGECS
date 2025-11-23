/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include <unordered_map>
#include "../components/Sprite.h"

// void spriteAnimationSystem(float dt) {
//     for (auto& [entity, sprite] : sprites) {
//         if (!sprite.animations.count(sprite.currentAnim)) continue;
//         Animation& anim = sprite.animations[sprite.currentAnim];

//         anim.tickCounter -= dt;
//         if (anim.tickCounter <= 0.0f) {
//             anim.tickCounter += anim.frameDelay;

//             // Advance frame within the animation range
//             sprite.curFrame++;
//             if (sprite.curFrame >= anim.startFrame + anim.numFrames) {
//                 sprite.curFrame = anim.startFrame; // loop animation
//             }
//         }
//     }
// }

void spriteAnimationSystem(float dt) {
    for (auto& [entity, sprite] : sprites) {
        if (!sprite.animations.count(sprite.currentAnim)) continue;
        Animation& anim = sprite.animations[sprite.currentAnim];

        anim.tickCounter -= dt;
        if (anim.tickCounter <= 0.0f) {
            anim.tickCounter += anim.frameDelay;

            // Advance the frame
            sprite.curFrame++;

            int animEnd = anim.startFrame + anim.numFrames;

            // --- NON-LOOPING ATTACK ANIMATION ---
            if (sprite.currentAnim == "attack") {
                if (sprite.curFrame >= animEnd) {
                    // Return to idle when attack finishes
                    sprite.currentAnim = "idle";
                    Animation& idle = sprite.animations["idle"];
                    sprite.curFrame = idle.startFrame;
                }
                continue; // Do NOT loop attack
            }

            // --- NORMAL LOOPING ANIMATIONS ---
            if (sprite.curFrame >= animEnd) {
                sprite.curFrame = anim.startFrame; // loop
            }
        }
    }
}
