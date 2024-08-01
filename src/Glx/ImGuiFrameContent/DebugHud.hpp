#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include "Flags.hpp"
#include "../GlWindow.hpp"

namespace Glx::ImGuiFrameContent
{
namespace DebugHud
{
inline bool Enabled = true;

inline void Tick()
{
    if (!Enabled)
        return;

    ImGui::SetNextWindowPos(ImVec2(1.f, 1.f));
    {
        ImGui::Begin("DebugHud", nullptr, Flags::HudFlags);
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

        ImGui::Text("fps: %.1f%s", ImGui::GetIO().Framerate,
                    GlWindow::VsyncEnabled ? " vsync" : "");

        ImGui::End();
    }
}

} // namespace DebugHud
} // namespace Glx::ImGuiFrameContent