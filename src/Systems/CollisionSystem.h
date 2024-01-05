#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

#include <SDL2/SDL.h>

class CollisionSystem: public System {
    public:
        CollisionSystem() {
            RequireComponent<BoxColliderComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update() {
            // Loop all entities that the system is interested in
            for (Entity entity: GetSystemEntities()) {
                const BoxColliderComponent& collider = entity.GetComponent<BoxColliderComponent>();
                TransformComponent& transform = entity.GetComponent<TransformComponent>();

                
            }
        }
};

#endif
