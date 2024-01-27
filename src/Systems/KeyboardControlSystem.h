#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class KeyboardControlSystem: public System {
    public:
        std::vector<SDL_KeyCode> keysPressed;

        KeyboardControlSystem() {
            RequireComponent<KeyboardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &KeyboardControlSystem::OnKeyReleased);
        }

        void OnKeyPressed(KeyPressedEvent& event) {
            switch (event.symbol) {
                case SDLK_UP:
                case SDLK_w:
                    keysPressed.push_back(SDLK_UP);
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    keysPressed.push_back(SDLK_RIGHT);
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    keysPressed.push_back(SDLK_DOWN);
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    keysPressed.push_back(SDLK_LEFT);
                    break;
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event) {
            const auto keyCode = event.symbol;
            keysPressed.erase(std::remove(keysPressed.begin(), keysPressed.end(), keyCode), keysPressed.end());
        }

        void Update() {
            for (auto entity: GetSystemEntities()) {
                const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

                if (keysPressed.size() == 0) {
                    rigidbody.velocity = glm::vec2(0);
                } else {
                    switch (keysPressed.back()) {
                        case SDLK_UP:
                        case SDLK_w:
                            rigidbody.velocity = keyboardcontrol.upVelocity;
                            rigidbody.direction = glm::vec2(0.0, -1.0);
                            sprite.srcRect.y = sprite.height * 0;
                            break;
                        case SDLK_RIGHT:
                        case SDLK_d:
                            rigidbody.velocity = keyboardcontrol.rightVelocity;
                            rigidbody.direction = glm::vec2(1.0, 0.0);
                            sprite.srcRect.y = sprite.height * 1;
                            break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            rigidbody.velocity = keyboardcontrol.downVelocity;
                            rigidbody.direction = glm::vec2(0.0, 1.0);
                            sprite.srcRect.y = sprite.height * 2;
                            break;
                        case SDLK_LEFT:
                        case SDLK_a:
                            rigidbody.velocity = keyboardcontrol.leftVelocity;
                            rigidbody.direction = glm::vec2(-1.0, 0.0);
                            sprite.srcRect.y = sprite.height * 3;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
};

#endif
