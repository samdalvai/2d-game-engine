#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

#include <SDL2/SDL.h>
#include <algorithm>

class RenderSystem: public System {
    public:
        RenderSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
            // TODO: sort entities by z-index
            std::vector<Entity> entities = GetSystemEntities();
            std::sort(entities.begin(), entities.end(), [](const Entity& a, const Entity& b) {
                const auto spriteA = a.GetComponent<SpriteComponent>();
                const auto spriteB = b.GetComponent<SpriteComponent>();

                return spriteA.zIndex < spriteB.zIndex;
            });

            // Loop all entities that the system is interested in
            for (Entity entity: entities) {
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto sprite = entity.GetComponent<SpriteComponent>();

                SDL_Rect destRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y),
                };

                SDL_RenderCopyEx(
                    renderer,
                    assetStore->GetTexture(sprite.assetId),
                    &sprite.srcRect,
                    &destRect, 
                    transform.rotation,
                    NULL,
                    SDL_FLIP_NONE
                );
            }
        }
};

#endif
