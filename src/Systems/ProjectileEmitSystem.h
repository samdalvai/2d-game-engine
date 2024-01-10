#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Event/CollisionEvent.h"

class ProjectileEmitSystem: public System {
    public:
        ProjectileEmitSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<ProjectileEmitterComponent>();
        }

        void Update() {
            
            
        }
};

#endif
