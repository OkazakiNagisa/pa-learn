#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <Singleton.hh>
#include "Flags.hpp"
#include "../GlWindow.hpp"

namespace Glx::ImGuiFrameContent
{
class DebugHud
{
public:
    bool Enabled = true;

    void Tick()
    {
        if (!Enabled)
            return;

        ImGui::SetNextWindowPos(ImVec2(1.f, 1.f));
        {
            ImGui::Begin("DebugHud", nullptr, Flags::HudFlags);
            ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

            ImGui::Text("fps: %.1f%s", ImGui::GetIO().Framerate,
                        Singleton::Get<GlWindow>().VsyncEnabled ? " vsync" : "");

            ImGui::End();
        }
    }
};
} // namespace Glx::ImGuiFrameContent