#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

#include <SDL2/SDL.h>

class AnimationSystem: public System {
    public:
        AnimationSystem() {
            RequireComponent<SpriteComponent>();
            RequireComponent<AnimationComponent>();
        }

        void Update() {
            // Loop all entities that the system is interested in
            for (Entity entity: GetSystemEntities()) {
                SpriteComponent& sprite = entity.GetComponent<SpriteComponent>();
                AnimationComponent& animation = entity.GetComponent<AnimationComponent>();
                
                SDL_Rect srcRect;

                animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000) % animation.numFrames;
                sprite.srcRect.x = animation.currentFrame * sprite.width;
                //sprite.srcRect.y = animation.currentFrame
            }
        }
};

#endif
