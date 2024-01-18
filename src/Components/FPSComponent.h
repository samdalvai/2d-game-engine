#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <string>

struct FPSComponent {
    glm::vec2 position;
    std::string assetId;
    SDL_Color color;

    FPSComponent(glm::vec2 position = glm::vec2(0), std::string assetId = "", const SDL_Color& color = { 0, 0, 0}) {
        this->position = position;
        this->assetId = assetId;
        this->color = color;
    };
};

#endif
