#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Event/CollisionEvent.h"

class DamageSystem: public System {
    public:
        DamageSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& event) {
            Logger::Log("Collision occurred between entities: " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));

            Entity& a = event.a;
            Entity& b = event.b;

            if (a.HasComponent<HealthComponent>()) {
                auto& health = a.GetComponent<HealthComponent>();
                health.healthPercentage -= 25;
                Logger::Log("Entity: " + std::to_string(event.a.GetId()) + " has now " + std::to_string(health.healthPercentage) + " of health");

                if (health.healthPercentage <= 0) {
                    a.Kill();
                }
            }

            if (b.HasComponent<HealthComponent>()) {
                auto& health = b.GetComponent<HealthComponent>();
                health.healthPercentage -= 25;
                Logger::Log("Entity: " + std::to_string(event.b.GetId()) + " has now " + std::to_string(health.healthPercentage) + " of health");

                if (health.healthPercentage <= 0) {
                    b.Kill();
                }
            }

            //event.a.Kill();
            //event.b.Kill();
        }

        void Update() {
            
        }
};

#endif
