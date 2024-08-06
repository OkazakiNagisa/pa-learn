#pragma once
#include <imgui.h>

namespace Glx::ImGuiFrameContent
{
class Flags
{
public:
    static const ImGuiWindowFlags BaseFlags =
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking;
    static const ImGuiWindowFlags HudFlags =
        BaseFlags | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground;
};
} // namespace Glx::ImGuiFrameContent