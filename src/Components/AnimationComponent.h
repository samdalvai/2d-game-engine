#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <glm/glm.hpp>
#include <string>

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameRateSpeed;
    bool shouldLoop;
    int startTime;

    AnimationComponent(int numFrames = 1, int currentFrame = 1, int frameRateSpeed = 1, bool shouldLoop = true) {
        this->numFrames = numFrames;
        this->currentFrame = currentFrame;
        this->frameRateSpeed = frameRateSpeed;
        this->shouldLoop = shouldLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif
