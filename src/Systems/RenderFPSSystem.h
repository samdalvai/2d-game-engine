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
            RequireComponent<TextLabelComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera) {
            for (auto entity : GetSystemEntities()) {
                auto& label = entity.GetComponent<TextLabelComponent>();
                auto& fpsComponent = entity.GetComponent<FPSComponent>();

                std::string text = "FPS: " + std::to_string(fpsComponent.currentFPS);

                SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(label.assetId), text.c_str(), label.color);

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                int labelWidth = 0;
                int labelHeight = 0;

                // Queries text font to extract width and height
                SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

                SDL_Rect destRect = {
                    static_cast<int>(label.position.x - ( label.isFixed ? 0 : camera.x)),
                    static_cast<int>(label.position.y - ( label.isFixed ? 0 : camera.y)),
                    labelWidth,
                    labelHeight
                };

                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }          
        }
};

#endif
