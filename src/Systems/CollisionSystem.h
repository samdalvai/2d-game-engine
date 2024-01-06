#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Event/CollisionEvent.h"

class CollisionSystem: public System {
    public:
        CollisionSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        void Update(std::unique_ptr<EventBus>& eventBus) {
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
                        
                        eventBus->EmitEvent<CollisionEvent>(a, b);
                    }
                }
            }
        }

        bool CheckAABBCollision(double aX, double aY, double aWidth, double aHeight, double bX, double bY, double bWidth, double bHeight) {
            return (
                aX < bX + bWidth &&
                aX + aWidth > bX &&
                aY < bY + bHeight &&
                aY + aHeight > bY
            );
        }
};

#endif
