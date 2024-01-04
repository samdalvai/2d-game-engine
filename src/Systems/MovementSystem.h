#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System {
    public:
        MovementSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void Update() {
            // Loop all entities that the system is interested in
            for (Entity entity: GetSystemEntities()) {
                TransformComponent& transform = entity.GetComponent<TransformComponent>();
                const RigidBodyComponent rigidBody = entity.GetComponent<RigidBodyComponent>();

                transform.position.x += rigidBody.velocity.x;
                transform.position.y += rigidBody.velocity.y;

                Logger::Log("Entity with id: " + std::to_string(entity.GetId()) + " position updated to (" + std::to_string(transform.position.x) + ", " + std::to_string(transform.position.y) + ")");
            }
        }
};

#endif
