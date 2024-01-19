#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../ECS/ECS.h"
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include <SDL2/SDL.h>

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

                static float enemyRotation = 0.0;
                static float enemyRotationMin = 0.0;
                static float enemmyRotationMax = 360.00;
                ImGui::SliderFloat("Enemy rotation", &enemyRotation, enemyRotationMin, enemmyRotationMax);

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

                if (ImGui::Button("Click to create enemy")) {
                    Entity enemy = registry->CreateEntity();
                    enemy.Group("enemies");
                    enemy.AddComponent<TransformComponent>(glm::vec2(enemyPositionX, enemyPositionY), glm::vec2(enemyscale, enemyscale), enemyRotation);
                    enemy.AddComponent<RigidBodyComponent>(glm::vec2(enemyVelocityX, enemyVelocityY));
                    enemy.AddComponent<SpriteComponent>(enemySpriteList[selectedSpriteIndex], 32, 32, 2);
                    enemy.AddComponent<BoxColliderComponent>(32, 32);
                    enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(0.0, 100.0), 2000, 5000, 25, false);
                    enemy.AddComponent<HealthComponent>(100);
                }
            }
            ImGui::End();

            ImGui::Render();
            ImGuiSDL::Render(ImGui::GetDrawData());
        }
};

#endif
