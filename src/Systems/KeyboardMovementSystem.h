#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Event/KeyPressedEvent.h"

class KeyBoardMovementSystem: public System {
    public:
        KeyBoardMovementSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyBoardMovementSystem::onKeyPressed);
        }

        void onKeyPressed(KeyPressedEvent& event) {
            
        }

        void Update() {
            
        }
};

#endif
