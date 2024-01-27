#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

#include <glm/glm.hpp>

class KeyboardControlSystem: public System {
    public:
        bool keyUpPressed;
        bool keyRightPressed;
        bool keyDownPressed;
        bool keyLeftPressed;

        KeyboardControlSystem() {
            RequireComponent<KeyboardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();

            this->keyUpPressed = false;
            this->keyRightPressed = false;
            this->keyDownPressed = false;
            this->keyLeftPressed = false;
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &KeyboardControlSystem::OnKeyReleased);
        }

        void OnKeyPressed(KeyPressedEvent& event) {
            switch (event.symbol) {
                case SDLK_UP:
                    keyUpPressed = true;
                    break;
                case SDLK_RIGHT:
                    keyRightPressed = true;
                    break;
                case SDLK_DOWN:
                    keyDownPressed = true;
                    break;
                case SDLK_LEFT:
                    keyLeftPressed = true;
                    break;
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event) {
            switch (event.symbol) {
                case SDLK_UP:
                    keyUpPressed = false;
                    break;
                case SDLK_RIGHT:
                    keyRightPressed = false;
                    break;
                case SDLK_DOWN:
                    keyDownPressed = false;
                    break;
                case SDLK_LEFT:
                    keyLeftPressed = false;
                    break;
            }
        }

        void Update() {
            for (auto entity: GetSystemEntities()) {
                const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

                if (keyUpPressed) {
                    rigidbody.velocity = keyboardcontrol.upVelocity;
                    sprite.srcRect.y = sprite.height * 0;
                } else if (rigidbody.velocity.y < 0) {
                    rigidbody.velocity.y = 0;
                }
                
                if (keyRightPressed) {
                    rigidbody.velocity = keyboardcontrol.rightVelocity;
                    sprite.srcRect.y = sprite.height * 1;
                } else if (rigidbody.velocity.x > 0) {
                    rigidbody.velocity.x = 0;
                }
                
                if (keyDownPressed) {
                    rigidbody.velocity = keyboardcontrol.downVelocity;
                    sprite.srcRect.y = sprite.height * 2;
                } else if (rigidbody.velocity.y > 0) {
                    rigidbody.velocity.y = 0;
                }
                
                if (keyLeftPressed) {
                    rigidbody.velocity = keyboardcontrol.leftVelocity;
                    sprite.srcRect.y = sprite.height * 3;
                } else if (rigidbody.velocity.x < 0) {
                    rigidbody.velocity.x = 0;
                }
            }
        }
};

#endif
