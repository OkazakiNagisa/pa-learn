#pragma once
#include <imgui.h>

namespace Glx::ImGuiFrameContent
{
namespace Flags
{

inline const ImGuiWindowFlags BaseFlags =
    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking;
inline const ImGuiWindowFlags HudFlags =
    BaseFlags | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
    ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground;

} // namespace Flags
} // namespace Glx::ImGuiFrameContent