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
        if (enemy.HasComponent<RigidBodyComponent>() && enemy.HasComponent<SpriteComponent>()) {
            auto& rigidBody = enemy.GetComponent<RigidBodyComponent>();
            auto& sprite = enemy.GetComponent<SpriteComponent>();

            if (rigidBody.velocity.x != 0) {
                rigidBody.velocity.x *= -1;
                sprite.flip = sprite.flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            }

            if (rigidBody.velocity.y != 0) {
                rigidBody.velocity.y *= -1;
                sprite.flip = sprite.flip == SDL_FLIP_NONE ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
            }
        }

    }

    void Update(double deltaTime) {
        // Loop all entities that the system is interested in
        for (auto entity : GetSystemEntities()) {
            // Update entity position based on its velocity
            auto &transform = entity.GetComponent<TransformComponent>();
            auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x * deltaTime;
            transform.position.y += rigidbody.velocity.y * deltaTime;

            // Prevent the main player from moving outside the map boundaries
            if (entity.HasTag("player")) {
                int padding = 10;

                int spritePaddingX = 0;
                int spritePaddingY = 0;
                if (entity.HasComponent<SpriteComponent>()) {
                    const auto sprite = entity.GetComponent<SpriteComponent>();

                    spritePaddingX = sprite.width;
                    spritePaddingY = sprite.height;
                }
                
                transform.position.x = transform.position.x < padding ? padding : transform.position.x;
                transform.position.x = transform.position.x > Game::mapWidth - (padding + spritePaddingX) ? Game::mapWidth - (padding + spritePaddingX) : transform.position.x;
                transform.position.y = transform.position.y < padding ? padding : transform.position.y;
                transform.position.y = transform.position.y > Game::mapHeight - (padding + spritePaddingY) ? Game::mapHeight - (padding + spritePaddingY) : transform.position.y;
            }

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
