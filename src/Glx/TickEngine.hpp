#pragma once
#include "Logging.hpp"
#include "GlWindow.hpp"
#include "ImGuiBase.hpp"

namespace Glx
{
namespace TickEngine
{
inline int Initialize()
{
    Logging::Initialize();
    if (!!GlWindow::Initialize())
        return -1;
    ImGuiBase::Initialize();

    return 0;
}

inline void PreTick()
{
    GlWindow::PreTick();
    ImGuiBase::PreTick();
}

inline void Tick()
{
    ImGuiBase::Tick();
}

inline void PostTick()
{
    ImGuiBase::PostTick();
    GlWindow::PostTick();
}

inline void Finalize()
{
    ImGuiBase::Finalize();
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