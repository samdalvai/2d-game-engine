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
        }

        static bool entitiesCollide(const BoxColliderComponent& colliderA, const BoxColliderComponent& colliderB, glm::vec2& positionA, glm::vec2& positionB) {
            int colliderAMinX = positionA.x + colliderA.offset.x;
            int colliderAMaxX = positionA.x + colliderA.width + colliderA.offset.x;
            int colliderBMinX = positionB.x + colliderB.offset.x;
            int colliderBMaxX = positionB.x + colliderB.width + colliderB.offset.x;

            if (colliderAMaxX < colliderBMinX || colliderAMinX > colliderBMaxX) return false;
            //if (box1.maxX < box2.minX || box1.minX > box2.maxX) return false;

            int colliderAMinY = positionA.y + colliderA.offset.y;
            int colliderAMaxY = positionA.y + colliderA.height + colliderA.offset.y;
            int colliderBMinY = positionB.y + colliderB.offset.y;
            int colliderBMaxY = positionB.y + colliderB.height + colliderB.offset.y;

            if (colliderAMaxY < colliderBMinY || colliderAMinY > colliderBMaxY) return false;

            //if (box1.maxY < box2.minY || box1.minY > box2.maxY) return false;

            return true;
        }

        void Update() {
            std::vector<Entity> entities = GetSystemEntities();
            for (int i = 0; i < entities.size(); i++) {
                const BoxColliderComponent& colliderA = entities[i].GetComponent<BoxColliderComponent>();
                TransformComponent& transformA = entities[i].GetComponent<TransformComponent>();
                for (int j = 1; j < entities.size(); j++) {
                    const BoxColliderComponent& colliderB = entities[i].GetComponent<BoxColliderComponent>();
                    TransformComponent& transformB = entities[i].GetComponent<TransformComponent>();

                    if (entitiesCollide(colliderA, colliderB, transformA.position, transformB.position)) {
                        Logger::Err("ENTITIES COLLIDE!!");
                    } else {
                        Logger::Log("ENTITIES DO NOT COLLIDE!!");
                    }
                }
            }

            /*std::vector<Entity> entities = GetSystemEntities();
            Logger::Log("ENTITIES SIZE: " + std::to_string(entities.size()));
            for (int i = 0; i < entities.size() - 1; i++) {
                const BoxColliderComponent& colliderA = entities[i].GetComponent<BoxColliderComponent>();
                TransformComponent& transformA = entities[i].GetComponent<TransformComponent>();
                for (int j = 1; j < entities.size(); j++) {
                    const BoxColliderComponent& colliderB = entities[i].GetComponent<BoxColliderComponent>();
                    TransformComponent& transformB = entities[i].GetComponent<TransformComponent>();
                    
                    if (entitiesCollide(colliderA, colliderB, transformA.position, transformB.position)) {
                        Logger::Log("ENTITIES COLLIDE!!");
                    }
                }
            }*/
        }
};

#endif
