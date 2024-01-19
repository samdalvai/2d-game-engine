#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <string>

struct FPSComponent {
    int currentFPS;

    FPSComponent(int currentFPS = 0) {
        this->currentFPS = currentFPS;
    };
};

#endif
