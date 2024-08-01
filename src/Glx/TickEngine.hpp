#pragma once
#include "Logging.hpp"
#include "GlWindow.hpp"
#include "ImGuiFrame.hpp"

namespace Glx
{
namespace TickEngine
{
inline int Initialize()
{
    Logging::Initialize();
    if (!!GlWindow::Initialize())
        return -1;
    ImGuiFrame::Initialize();

    return 0;
}

inline void PreTick()
{
    GlWindow::PreTick();
    ImGuiFrame::PreTick();
}

inline void Tick() {}

inline void PostTick()
{
    ImGuiFrame::PostTick();
}

inline void Finalize()
{
    ImGuiFrame::Finalize();
    GlWindow::Finalize();
    Logging::Finalize();
}

inline void Run()
{
    Initialize();
    while (!glfwWindowShouldClose(GlWindow::GlfwWindowPtr))
    {
        PreTick();
        Tick();
        PostTick();
    }
    Finalize();
}
} // namespace TickEngine
} // namespace Glx