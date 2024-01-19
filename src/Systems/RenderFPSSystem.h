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

        void Update(int millisecsPreviousFrame, int millisecsCurrentFrame) {
            for (auto entity : GetSystemEntities()) {
                auto& label = entity.GetComponent<TextLabelComponent>();
                auto& fpsComponent = entity.GetComponent<FPSComponent>();

                if (millisecsCurrentFrame - fpsComponent.millisecsPreviousMeasurement >= 1000) {
                    int computedFps = 1000 / (millisecsCurrentFrame - millisecsPreviousFrame);

                    label.text = "FPS: " + std::to_string(computedFps);
                    fpsComponent.millisecsPreviousMeasurement = millisecsCurrentFrame;
                }
            }          
        }
};

#endif
