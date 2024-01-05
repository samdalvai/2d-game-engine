#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

#include <SDL2/SDL.h>
#include <algorithm>

class AnimationSystem: public System {
    public:
        AnimationSystem() {
            RequireComponent<SpriteComponent>();
            RequireComponent<AnimationComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
            // Loop all entities that the system is interested in
            for (Entity entity: GetSystemEntities()) {
                const SpriteComponent& sprite = entity.GetComponent<SpriteComponent>();
                const AnimationComponent& animation = entity.GetComponent<AnimationComponent>();
                
                
            }
        }
};

#endif
