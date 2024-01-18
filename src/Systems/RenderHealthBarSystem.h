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
                SDL_Color white = { 255, 255, 255};

                SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(assetId), percentage.c_str(), white);

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                int labelWidth = 0;
                int labelHeight = 0;

                // Queries text font to extract width and height
                SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

                SDL_Rect destRect = {
                    static_cast<int>(transform.position.x - camera.x),
                    static_cast<int>(transform.position.y - sprite.height / 2 - camera.y),
                    labelWidth,
                    labelHeight
                };
                
                SDL_RenderCopy(renderer, texture, NULL, &destRect);

                /*const auto textLabel = entity.GetComponent<TextLabelComponent>();
                
                SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(textLabel.assetId), textLabel.text.c_str(), textLabel.color);

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                int labelWidth = 0;
                int labelHeight = 0;

                // Queries text font to extract width and height
                SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

                SDL_Rect destRect = {
                    static_cast<int>(textLabel.position.x - ( textLabel.isFixed ? 0 : camera.x)),
                    static_cast<int>(textLabel.position.y - ( textLabel.isFixed ? 0 : camera.y)),
                    labelWidth,
                    labelHeight
                };

                SDL_RenderCopy(renderer, texture, NULL, &destRect);*/
            }           
        }
};

#endif
