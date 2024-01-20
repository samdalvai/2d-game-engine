#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../ECS/ECS.h"
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <string>

class RenderGUISystem: public System {
    public:
        RenderGUISystem() {}

        void Update(std::unique_ptr<Registry>& registry) {
            ImGui::NewFrame();
            
            if (ImGui::Begin("Spawn enemies")) {
                ImGui::Text("Spawn new enemy");
                static int enemyPositionX = 100;
                ImGui::InputInt("Enemey position x", &enemyPositionX);

                static int enemyPositionY = 100;
                ImGui::InputInt("Enemy position y", &enemyPositionY);

                static double enemyscale = 1.0;
                ImGui::InputDouble("Enemy scale", &enemyscale);

                static float enemyRotationRadians = 0.0;
                ImGui::SliderAngle("Enemy rotation angle", &enemyRotationRadians);
                float enemyRotationDegrees = enemyRotationRadians * 180.0 / M_PI;

                //M_PI

                static int enemyVelocityX = 0;
                static int enemyVelocityY = 0;
                ImGui::InputInt("Enemy velocity x", &enemyVelocityX);
                ImGui::InputInt("Enemy velocity y", &enemyVelocityY);

                std::vector<std::string> enemySpriteList = { "truck-image", "tank-image" };
                static int selectedSpriteIndex = 0;
                static bool showDropdown = false;

                if (ImGui::Button("Select enemy sprite")){
                    showDropdown = !showDropdown;
                }

                if (showDropdown){
                    ImGui::Begin("Enemy sprite dropdown");
                    for (int i = 0; i < enemySpriteList.size(); ++i)
                    {
                        if (ImGui::Selectable(enemySpriteList[i].c_str())) {
                            selectedSpriteIndex = i;
                            showDropdown = false;
                        }
                    }
                    ImGui::End();
                }
                ImGui::Text("Selected sprite: %s", enemySpriteList[selectedSpriteIndex].c_str());

                static float enemyProjectileRadians = 0.0;
                ImGui::SliderAngle("Enemy projectile angle", &enemyProjectileRadians);
                static int enemyProjectileSpeed = 100;
                ImGui::InputInt("Enemy projectile speed", &enemyProjectileSpeed);

                double enemyProjectileVelocityX = std::cos(enemyProjectileRadians) * enemyProjectileSpeed;
                double enemyProjectileVelocityY = std::sin(enemyProjectileRadians) * enemyProjectileSpeed;

                static int enemyProjectileFrequency = 1000;
                ImGui::InputInt("Enemy projectile frequency", &enemyProjectileFrequency);

                static int enemyProjectileDuration = 5000;
                ImGui::InputInt("Enemy projectile duration", &enemyProjectileDuration);

                //static int enemyProjectileDuration = 5000;
                static int enemyHealthPercentageMin = 10;
                static int enemyHealthPercentageMax = 100;
                static int enemyHealthPercentage = 50;
                ImGui::SliderInt("Enemy health percentage", &enemyHealthPercentage, enemyHealthPercentageMin, enemyHealthPercentageMax);

                if (ImGui::Button("Click to create enemy")) {
                    Entity enemy = registry->CreateEntity();
                    enemy.Group("enemies");
                    enemy.AddComponent<TransformComponent>(glm::vec2(enemyPositionX, enemyPositionY), glm::vec2(enemyscale, enemyscale), enemyRotationDegrees);
                    enemy.AddComponent<RigidBodyComponent>(glm::vec2(enemyVelocityX, enemyVelocityY));
                    enemy.AddComponent<SpriteComponent>(enemySpriteList[selectedSpriteIndex], 32, 32, 2);
                    enemy.AddComponent<BoxColliderComponent>(32, 32);
                    enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(enemyProjectileVelocityX, enemyProjectileVelocityY), enemyProjectileFrequency, enemyProjectileDuration, 25, false);
                    enemy.AddComponent<HealthComponent>(enemyHealthPercentage);
                }
            }
            ImGui::End();

            ImGui::Render();
            ImGuiSDL::Render(ImGui::GetDrawData());
        }
};

#endif
