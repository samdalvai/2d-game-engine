#ifndef RENDERCOLLISIONSYSTEM_H
#define RENDERCOLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/BoxColliderComponent.h"

#include <SDL2/SDL.h>
#include <algorithm>

class RenderCollisionSystem: public System {
    public:
        RenderCollisionSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void Update(SDL_Renderer* renderer) {
            
        }
};

#endif
