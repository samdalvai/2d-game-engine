#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"

#include <SDL2/SDL.h>

class CameraMovementSystem: public System {
    public:
        CameraMovementSystem() {
            RequireComponent<CameraFollowComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update() {
            
        }
};

#endif
