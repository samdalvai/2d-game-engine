#ifndef RENDERFPSSYSTEM_H
#define RENDERFPSSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/FPSComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>
#include <string>

class RenderFPSSystem: public System {
    public:
        RenderFPSSystem() {
            RequireComponent<FPSComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera, int millisecsPreviousFrame) {
            for (auto entity : GetSystemEntities()) {
                const auto fps = entity.GetComponent<FPSComponent>();

                std::string text = "FPS: " + std::to_string(SDL_GetTicks() - millisecsPreviousFrame);
                
                SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(fps.assetId), text.c_str(), fps.color);

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                int labelWidth = 0;
                int labelHeight = 0;

                // Queries text font to extract width and height
                SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

                SDL_Rect destRect = {
                    static_cast<int>(fps.position.x - camera.x),
                    static_cast<int>(fps.position.y - camera.y),
                    labelWidth,
                    labelHeight
                };

                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }          
        }
};

#endif
