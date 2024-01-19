#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <string>

struct FPSComponent {
    int currentFPS;
    int millisecsPreviousFrame;
    int millisecsUpdateFrequency;

    FPSComponent(int currentFPS = 0, int millisecsPreviousFrame = 0, int millisecsUpdateFrequency = 1000) {
        this->currentFPS = currentFPS;
        this->millisecsPreviousFrame = millisecsPreviousFrame;
        this->millisecsUpdateFrequency = millisecsUpdateFrequency;
    };
};

#endif
