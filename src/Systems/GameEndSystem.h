#ifndef GAMEENDSYSTEM_H
#define GAMEENDSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextLabelComponent.h"
#include <SDL2/SDL.h>

class GameEndSystem: public System {
    public:
        GameEndSystem() {
            RequireComponent<HealthComponent>();
        }

        void Update(std::unique_ptr<Registry>& registry) {
            int numberOfEnemies = 0;
            bool isPlayerAlive = false;
            
            for (auto entity: GetSystemEntities()) {
                if (entity.BelongsToGroup("enemies")) {
                    numberOfEnemies++;
                }

                if (entity.HasTag("player")) {
                    isPlayerAlive = true;
                }
            }

            if (numberOfEnemies == 0) {
                Entity label = registry->CreateEntity();
                SDL_Color color = { 100, 255, 100};
                label.AddComponent<TextLabelComponent>(glm::vec2(Game::windowWidth / 2 - 50, Game::windowHeight / 2), "Game won!!", "charriot-font-xl", color, true);
                return;
            }

            if (!isPlayerAlive) {
                Entity label = registry->CreateEntity();
                SDL_Color color = { 255, 50, 50};
                label.AddComponent<TextLabelComponent>(glm::vec2(Game::windowWidth / 2 - 50, Game::windowHeight / 2), "Game lost!", "charriot-font-xl", color, true);
            }
        }
};

#endif