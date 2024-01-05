#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class CollisionSystem: public System {
    public:
        CollisionSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        static bool entitiesCollide(const BoxColliderComponent& colliderA, const BoxColliderComponent& colliderB, glm::vec2& positionA, glm::vec2& positionB) {
            int colliderAMinX = positionA.x + colliderA.offset.x;
            int colliderAMaxX = positionA.x + colliderA.width + colliderA.offset.x;
            int colliderBMinX = positionB.x + colliderB.offset.x;
            int colliderBMaxX = positionB.x + colliderB.width + colliderB.offset.x;

            if (colliderAMaxX < colliderBMinX || colliderAMinX > colliderBMaxX) return false;

            int colliderAMinY = positionA.y + colliderA.offset.y;
            int colliderAMaxY = positionA.y + colliderA.height + colliderA.offset.y;
            int colliderBMinY = positionB.y + colliderB.offset.y;
            int colliderBMaxY = positionB.y + colliderB.height + colliderB.offset.y;

            if (colliderAMaxY < colliderBMinY || colliderAMinY > colliderBMaxY) return false;

            return true;
        }

        void Update() {
            std::vector<Entity> entities = GetSystemEntities();
            for (int i = 0; i < entities.size() - 1 && !entities.empty() != 0; i++) {
                Entity entityA = entities[i];
                const BoxColliderComponent& colliderA = entityA.GetComponent<BoxColliderComponent>();
                TransformComponent& transformA = entityA.GetComponent<TransformComponent>();
                for (int j = i + 1; j < entities.size(); j++) {
                    Entity entityB = entities[j];
                    const BoxColliderComponent& colliderB = entityB.GetComponent<BoxColliderComponent>();
                    TransformComponent& transformB = entityB.GetComponent<TransformComponent>();

                    if (entitiesCollide(colliderA, colliderB, transformA.position, transformB.position)) {
                        RigidBodyComponent& rigidBodyA = entityA.GetComponent<RigidBodyComponent>();
                        RigidBodyComponent& rigidBodyB = entityB.GetComponent<RigidBodyComponent>();

                        rigidBodyA.velocity = glm::vec2(0.0, 0.0);
                        rigidBodyB.velocity = glm::vec2(0.0, 0.0);
                    }
                }
            }
        }
};

#endif
