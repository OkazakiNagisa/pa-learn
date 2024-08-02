#pragma once
#include "Logging.hpp"
#include "GlWindow.hpp"
#include "ImGuiBaseFrame.hpp"

namespace Glx
{
namespace TickEngine
{

inline int Initialize()
{
    Logging::Initialize();
    if (!!GlWindow::Initialize())
        return -1;
    ImGuiBaseFrame::Initialize();

    return 0;
}

inline void PreTick()
{
    GlWindow::PreTick();
    ImGuiBaseFrame::PreTick();
}

inline void Tick()
{
    ImGuiBaseFrame::Tick();
}

inline void PostTick()
{
    ImGuiBaseFrame::PostTick();
    GlWindow::PostTick();
}

inline void Finalize()
{
    ImGuiBaseFrame::Finalize();
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