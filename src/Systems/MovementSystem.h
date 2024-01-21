#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class MovementSystem : public System {
public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
    }

    void OnCollision(CollisionEvent& event) {
        Entity a = event.a;
        Entity b = event.b;
        Logger::Log("Collision event emitted: " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));
    
        if (a.BelongsToGroup("enemies") && b.BelongsToGroup("obstacles")) {
            OnEnemyHitsObstacle(a);
        }

        if (a.BelongsToGroup("obstacles") && b.BelongsToGroup("enemies")) {
            OnEnemyHitsObstacle(b);
        }
    }

    void OnEnemyHitsObstacle(Entity enemy) {
        if (enemy.HasComponent<RigidBodyComponent>()) {
            auto& rigidBody = enemy.GetComponent<RigidBodyComponent>();

            if (rigidBody.velocity.x != 0) {
                rigidBody.velocity.x *= -1;
            }

            if (rigidBody.velocity.y != 0) {
                rigidBody.velocity.y *= -1;
            }
        }

    }

    void Update(double deltaTime) {
        // Loop all entities that the system is interested in
        for (auto entity : GetSystemEntities()) {
            // Update entity position based on its velocity
            auto &transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x * deltaTime;
            transform.position.y += rigidbody.velocity.y * deltaTime;

            bool isEntityOutsideMap = transform.position.x < 0 ||
                                      transform.position.x > Game::mapWidth ||
                                      transform.position.y < 0 ||
                                      transform.position.y > Game::mapHeight;

            if (isEntityOutsideMap && !entity.HasTag("player")) {
                entity.Kill();
            }
        }
    }
};

#endif
