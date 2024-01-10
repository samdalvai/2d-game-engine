#ifndef RENDERCOLLISIONSYSTEM_H
#define RENDERCOLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

#include <SDL2/SDL.h>

class RenderCollisionSystem: public System {
    public:
        RenderCollisionSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
            for (Entity entity: GetSystemEntities()) {
                auto transform = entity.GetComponent<TransformComponent>();
                auto collider = entity.GetComponent<BoxColliderComponent>();

                SDL_Rect boxColliderRect = {
                    static_cast<int>(transform.position.x - camera.x),
                    static_cast<int>(transform.position.y - camera.y),
                    static_cast<int>(collider.width * transform.scale.x),
                    static_cast<int>(collider.height * transform.scale.y),
                };

                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &boxColliderRect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
        }
};

#endif
