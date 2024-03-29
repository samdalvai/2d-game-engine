#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <vector>
#include <iostream>

class RenderGUISystem: public System {
    public:
        RenderGUISystem() = default;

        void Update(const std::unique_ptr<Registry>& registry, const SDL_Rect& camera) {
            ImGui::NewFrame();

            RenderSpawnEnemiesMenu(registry, camera);

            RenderMapsPositionMenu(camera);

            RenderFPSMenu();

            RenderLogsMenu();

            ImGui::Render();
            ImGuiSDL::Render(ImGui::GetDrawData());
        }

        void RenderSpawnEnemiesMenu(const std::unique_ptr<Registry>& registry, const SDL_Rect& camera) {
            if (ImGui::Begin("Spawn enemies")) {
                static int posX = camera.x + 100;
                static int posY = camera.y + 100;
                static int scaleX = 1;
                static int scaleY = 1;
                static int velX = 0;
                static int velY = 0;
                static int health = 100;
                static float rotation = 0.0;
                static float projAngle = 0.0;
                static float projSpeed = 100.0;
                static int projRepeat = 1;
                static int projDuration = 10;
                const char* sprites[] = {"tank-tiger-right-texture", "truck-ford-right-texture"};
                static int selectedSpriteIndex = 0;

                if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::Combo("texture id", &selectedSpriteIndex, sprites, IM_ARRAYSIZE(sprites));
                }
                ImGui::Spacing();

                if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::InputInt("position x", &posX);
                    ImGui::InputInt("position y", &posY);
                    ImGui::SliderInt("scale x", &scaleX, 1, 10);
                    ImGui::SliderInt("scale y", &scaleY, 1, 10);
                    ImGui::SliderAngle("rotation (deg)", &rotation, 0, 360);
                }
                ImGui::Spacing();

                if (ImGui::CollapsingHeader("Rigid body", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::InputInt("velocity x", &velX);
                    ImGui::InputInt("velocity y", &velY);
                }
                ImGui::Spacing();

                if (ImGui::CollapsingHeader("Projectile emitter", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::SliderAngle("angle (deg)", &projAngle, 0, 360);
                    ImGui::SliderFloat("speed (px/sec)", &projSpeed, 10, 500);
                    ImGui::InputInt("repeat (sec)", &projRepeat);
                    ImGui::InputInt("duration (sec)", &projDuration);
                }
                ImGui::Spacing();

                if (ImGui::CollapsingHeader("Health", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::SliderInt("%", &health, 0, 100);
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                if (ImGui::Button("Spawn new enemy")) {
                    Entity enemy = registry->CreateEntity();
                    enemy.Group("enemies");
                    enemy.AddComponent<TransformComponent>(glm::vec2(posX, posY), glm::vec2(scaleX, scaleY), glm::degrees(rotation));
                    enemy.AddComponent<RigidBodyComponent>(glm::vec2(velX, velY));
                    enemy.AddComponent<SpriteComponent>(sprites[selectedSpriteIndex], 32, 32, 2);
                    enemy.AddComponent<BoxColliderComponent>(25, 20, glm::vec2(5, 5));
                    double projVelX = cos(projAngle) * projSpeed; // convert from angle-speed to x-value
                    double projVelY = sin(projAngle) * projSpeed; // convert from angle-speed to y-value
                    enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(projVelX, projVelY), projRepeat * 1000, projDuration * 1000, 10, false);
                    enemy.AddComponent<HealthComponent>(health);

                    posX = camera.x + 100;
                    posY = camera.y + 100;
                    rotation = projAngle = 0;
                    scaleX = scaleY = 1;
                    projRepeat = 1;
                    projDuration = 10;
                    projSpeed = 100;
                    health = 100;
                }
            }
            ImGui::End();
        }

        void RenderMapsPositionMenu(const SDL_Rect& camera) {
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always, ImVec2(0, 0));
            ImGui::SetNextWindowBgAlpha(0.9f);
            if (ImGui::Begin("Map coordinates", NULL, windowFlags)) {
                ImGui::Text(
                    "Map coordinates (x=%.1f, y=%.1f)",
                    ImGui::GetIO().MousePos.x + camera.x,
                    ImGui::GetIO().MousePos.y + camera.y
                );
            }
            ImGui::End();
        }

        void RenderFPSMenu() {
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
            ImGui::SetNextWindowPos(ImVec2(10, 50), ImGuiCond_Always, ImVec2(0, 0));
            ImGui::SetNextWindowBgAlpha(0.9f);
            if (ImGui::Begin("FPS Counter", NULL, windowFlags)) {
                ImGui::Text("Current FPS: (%i) frames/second", Game::currentFPS);
            }
            ImGui::End();
        }

        void RenderLogsMenu() { 
            ImGui::Begin("Message Log", nullptr, ImGuiWindowFlags_HorizontalScrollbar);

            const std::vector<LogEntry>& logEntries = Logger::GetLastMessages(50);

            for (const auto& logEntry : logEntries) {
                if (logEntry.type == LOG_ERROR) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                }
                ImGui::TextUnformatted(logEntry.message.c_str());
                ImGui::PopStyleColor();
            }

            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);

            ImGui::End();
        }
};

#endif
