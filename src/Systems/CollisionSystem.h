#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class CollisionSystem: public System {
    public:
        CollisionSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        void Update() {
            auto entities = GetSystemEntities();

            // Loop all the entities that the system is interested in
            for (int i = 0; i < entities.size() - 1 && !entities.empty(); i++) {
                Entity a = entities[i];
                auto aTransform = a.GetComponent<TransformComponent>();
                BoxColliderComponent& aCollider = a.GetComponent<BoxColliderComponent>();

                // Loop all the entities that still need to be checked (to the right of i)
                for (int j = i + 1; j < entities.size(); j++) {
                    Entity b = entities[j];

                    auto bTransform = b.GetComponent<TransformComponent>();
                    BoxColliderComponent& bCollider = b.GetComponent<BoxColliderComponent>();
                 
                    // Perform the AABB collision check between entities a and b
                    bool collisionHappened = CheckAABBCollision(
                        aTransform.position.x + aCollider.offset.x,
                        aTransform.position.y + aCollider.offset.y,
                        aCollider.width * aTransform.scale.x,
                        aCollider.height* aTransform.scale.y,
                        bTransform.position.x + bCollider.offset.x,
                        bTransform.position.y + bCollider.offset.y,
                        bCollider.width * bTransform.scale.x,
                        bCollider.height * bTransform.scale.y
                    );

                    if (collisionHappened) {
                        Logger::Log("Entity " + std::to_string(a.GetId()) + " is colliding with entity " + std::to_string(b.GetId()));
                        
                        aCollider.isColliding = true;
                        bCollider.isColliding = true;
                    } else {
                        aCollider.isColliding = false;
                        bCollider.isColliding = false;
                    }
                }
            }
        }

        bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
            return (
                aX < bX + bW &&
                aX + aW > bX &&
                aY < bY + bH &&
                aY + aH > bY
            );
        }
};

#endif
