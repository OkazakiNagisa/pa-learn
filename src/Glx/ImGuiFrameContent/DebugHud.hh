#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <Singleton.hh>
#include "Flags.hh"
#include "../GlWindow.hh"

namespace Glx::ImGuiFrameContent
{
class DebugHud
{
public:
    DebugHud(GlWindow &glWindow) : GlWindowInstance(glWindow) {}

    void Tick()
    {
        if (!Enabled)
            return;

        ImGui::SetNextWindowPos(ImVec2(1.f, 1.f));
        {
            ImGui::Begin("DebugHud", nullptr, Flags::HudFlags);
            ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

            ImGui::Text("fps: %.1f%s", ImGui::GetIO().Framerate,
                        GlWindowInstance.VsyncEnabled ? " vsync" : "");

            ImGui::End();
        }
    }

private:
    bool Enabled = true;
    GlWindow &GlWindowInstance;
};
} // namespace Glx::ImGuiFrameContent