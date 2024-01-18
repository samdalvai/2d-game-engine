#ifndef RENDERFPSSYSTEM_H
#define RENDERFPSSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/FPSComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

class RenderFPSSystem: public System {
    public:
        RenderFPSSystem() {
            RequireComponent<TextLabelComponent>();
            RequireComponent<FPSComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera) {
            for (auto entity : GetSystemEntities()) {
                
            }           
        }
};

#endif
