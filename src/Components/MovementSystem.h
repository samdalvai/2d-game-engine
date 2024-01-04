#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct MovementSystem {
    glm::vec2 velocity;

    MovementSystem(glm::vec2 velocity = glm::vec2(0.0, 0.0)) {
        this->velocity = velocity;
    }
};

#endif
