#ifndef FPSSYSTEM_H
#define FPSSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/FPSComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>
#include <string>

class FPSSystem: public System {
    public:
        FPSSystem() {
            RequireComponent<FPSComponent>();
        }

        void Update(int millisecsPreviousFrame, int millisecsCurrentFrame) {
            for (auto entity : GetSystemEntities()) {
                auto& fpsComponent = entity.GetComponent<FPSComponent>();

                if (millisecsCurrentFrame - fpsComponent.millisecsPreviousFrame >= fpsComponent.millisecsUpdateFrequency) {
                    int computedFps = 1000 / (millisecsCurrentFrame - millisecsPreviousFrame);

                    fpsComponent.currentFPS = computedFps;
                    fpsComponent.millisecsPreviousFrame = millisecsCurrentFrame;
                }
            }          
        }
};

#endif
