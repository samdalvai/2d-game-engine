#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/BoxColliderComponent.h"

#include <SDL2/SDL.h>

class CollisionSystem: public System {
    public:
        CollisionSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void Update(std::unique_ptr<AssetStore>& assetStore) {
            // Loop all entities that the system is interested in
            for (Entity entity: GetSystemEntities()) {
                const BoxColliderComponent& collider = entity.GetComponent<BoxColliderComponent>();

            }
        }
};

#endif
