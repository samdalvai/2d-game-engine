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

                if (ImGui::Button("Click to create enemy")) {
                    Entity enemy = registry->CreateEntity();
                    enemy.Group("enemies");
                    enemy.AddComponent<TransformComponent>(glm::vec2(enemyPositionX, enemyPositionY), glm::vec2(1.0, 1.0), 0.0);
                    enemy.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
                    enemy.AddComponent<SpriteComponent>("truck-image", 32, 32, 2);
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
