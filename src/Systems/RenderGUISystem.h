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

        void Update() {
            ImGui::NewFrame();
            ImGui::ShowDemoWindow();
            ImGui::Render();
            ImGuiSDL::Render(ImGui::GetDrawData());
        }
};

#endif
