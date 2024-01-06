#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/BoxColliderComponent.h"
#include "../Event/CollisionEvent.h"

class DamageSystem: public System {
    public:
        DamageSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
        }

        void onCollision(CollisionEvent& event) {

        }

        void Update() {
            
        }
};

#endif
