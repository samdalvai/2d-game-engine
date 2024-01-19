#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <string>

struct FPSComponent {
    int millisecsPreviousMeasurement;

    FPSComponent(int millisecsPreviousMeasurement = 0) {
        this->millisecsPreviousMeasurement = millisecsPreviousMeasurement;
    };
};

#endif
