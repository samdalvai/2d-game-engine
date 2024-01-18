#ifndef RENDERHEALTHBARSYSTEM_H
#define RENDERHEALTHBARSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

class RenderHealthBarSystem: public System {
    public:
        RenderHealthBarSystem() {
            RequireComponent<HealthComponent>();
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera, const std::string& assetId) {
            for (auto entity : GetSystemEntities()) {
                auto transform = entity.GetComponent<TransformComponent>();
                auto health = entity.GetComponent<HealthComponent>();
                auto sprite = entity.GetComponent<SpriteComponent>();

                std::string percentage = std::to_string(health.healthPercentage) + "%";
                SDL_Color color = { 255, 255, 255}; // white

                if (health.healthPercentage <= 35) {
                    color = { 255, 0, 0}; // red
                } else if (health.healthPercentage <= 75) {
                    color = { 255, 255, 0}; // yellow
                }

                SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(assetId), percentage.c_str(), color);

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                int labelWidth = 0;
                int labelHeight = 0;

                // Queries text font to extract width and height
                SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

                SDL_Rect destRect = {
                    static_cast<int>(transform.position.x - camera.x),
                    static_cast<int>(transform.position.y - sprite.height / 4 - camera.y - labelHeight),
                    labelWidth,
                    labelHeight
                };
                
                SDL_RenderCopy(renderer, texture, NULL, &destRect);

                SDL_Rect healthBarRect = {
                    static_cast<int>(transform.position.x - camera.x),
                    static_cast<int>(transform.position.y - sprite.height / 4 - camera.y),
                    health.healthPercentage / 3,
                    5
                };

                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                SDL_RenderFillRect(renderer, &healthBarRect);
            }           
        }
};

#endif
