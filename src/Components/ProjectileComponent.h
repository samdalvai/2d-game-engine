#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct ProjectileComponent {
    bool isFriendly;
    int hitPercentDamage;
    int projectileDuration;
    int startTime;

    ProjectileComponent(bool isFriendly = false, int hitPercentDamage = 0, int projectileDuration = 0) {
        this->isFriendly = isFriendly;
        this->hitPercentDamage = hitPercentDamage;
        this->projectileDuration = projectileDuration;
        this->startTime = SDL_GetTicks();
    }
};

#endif
