#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Game/Game.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

class MovementSystem: public System {
    public:
        MovementSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void SubscribeToEvents(const std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
        }
        
        void OnCollision(CollisionEvent& event) {
            Entity a = event.a;
            Entity b = event.b;
            if (a.BelongsToGroup("enemies") && b.BelongsToGroup("obstacles")) {
                OnEnemyHitsObstacle(a);
            }
            if (a.BelongsToGroup("obstacles") && b.BelongsToGroup("enemies")) {
                OnEnemyHitsObstacle(b);
            }

            if (a.HasTag("player") && (b.BelongsToGroup("enemies") || (b.BelongsToGroup("obstacles")))) {
                OnPlayerHitsEnemyOrObstacle(a);
            }
            if ((a.BelongsToGroup("enemies") || a.BelongsToGroup("obstacles")) && b.HasTag("player")) {
                OnPlayerHitsEnemyOrObstacle(b);
            }
        }

        void OnEnemyHitsObstacle(Entity enemy) {
            if (enemy.HasComponent<RigidBodyComponent>() && enemy.HasComponent<SpriteComponent>()) {
                auto& rigidbody = enemy.GetComponent<RigidBodyComponent>();
                auto& sprite = enemy.GetComponent<SpriteComponent>();

                if (rigidbody.velocity.x != 0) {
                    rigidbody.velocity.x *= -1;
                    sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
                }
                
                if (rigidbody.velocity.y != 0) {
                    rigidbody.velocity.y *= -1;
                    sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
                }
            }
        }

        void OnPlayerHitsEnemyOrObstacle(Entity player) {
            if (player.HasComponent<RigidBodyComponent>() && player.HasComponent<TransformComponent>()) {
                auto& rigidbody = player.GetComponent<RigidBodyComponent>();
                auto& transform = player.GetComponent<TransformComponent>();
                
                // Move player some pixels back on collision to avoid being stuck
                if (rigidbody.velocity.x > 0) {
                    transform.position.x -= 10.0;
                }

                if (rigidbody.velocity.x < 0) {
                    transform.position.x += 10.0;
                }

                if (rigidbody.velocity.y > 0) {
                    transform.position.y -= 10.0;
                }

                if (rigidbody.velocity.y < 0) {
                    transform.position.y += 10.0;
                }

                rigidbody.velocity = glm::vec2(0);
            }
        }

        void Update(double deltaTime) {
            // Loop all entities that the system is interested in
            for (auto entity: GetSystemEntities()) {
                // Update entity position based on its velocity
                auto& transform = entity.GetComponent<TransformComponent>();
                const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

                // Update the entity position based on its velocity
                transform.position.x += rigidbody.velocity.x * deltaTime; 
                transform.position.y += rigidbody.velocity.y * deltaTime; 

                // Prevent the main player from moving outside the map boundaries
                if (entity.HasTag("player")) {
                    int paddingLeft = 10;
                    int paddingTop = 10;
                    int paddingRight = 50;
                    int paddingBottom = 50;
                    transform.position.x = transform.position.x < paddingLeft ? paddingLeft : transform.position.x;
                    transform.position.x = transform.position.x > Game::mapWidth - paddingRight ? Game::mapWidth - paddingRight : transform.position.x;
                    transform.position.y = transform.position.y < paddingTop ? paddingTop : transform.position.y;
                    transform.position.y = transform.position.y > Game::mapHeight - paddingBottom ? Game::mapHeight - paddingBottom : transform.position.y;
                }

                // Check if entity is outside the map boundaries (with a 200 pixels forgiving culling margin)
                int cullingMargin = 200;
                
                bool isEntityOutsideMap = (
                    transform.position.x < -cullingMargin ||
                    transform.position.x > Game::mapWidth + cullingMargin ||
                    transform.position.y < -cullingMargin ||
                    transform.position.y > Game::mapHeight + cullingMargin
                );

                // Kill all entities that move outside the map boundaries
                if (isEntityOutsideMap && !entity.HasTag("player")) {
                    entity.Kill();
                }
            }
        }
};

#endif
