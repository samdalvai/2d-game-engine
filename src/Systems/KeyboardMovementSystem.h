#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Event/KeyPressedEvent.h"

#include <SDL2/SDL.h>

class KeyBoardMovementSystem: public System {
    public:
        KeyBoardMovementSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyBoardMovementSystem::OnKeyPressed);
        }

        void OnKeyPressed(KeyPressedEvent& event) {
            Logger::Log("Key pressed event, key code: " + std::to_string(event.keyCode) + 
             ", key name: " + SDL_GetKeyName(event.keyCode));
        }

        void Update() {
            
        }
};

#endif
