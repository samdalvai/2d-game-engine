#ifndef RENDERHEALTHBARSYSTEM_H
#define RENDERHEALTHBARSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

class RenderHealthBarSystem: public System {
    public:
        RenderHealthBarSystem() {
            RequireComponent<HealthComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
            for (auto entity : GetSystemEntities()) {

                

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
