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

            if (numberOfEnemies == 0 && Game::gameStatus != WON) {
                Game::gameStatus = WON;
            }

            if (!isPlayerAlive && Game::gameStatus != LOST) {
                Game::gameStatus = LOST;
            }
        }
};

#endif