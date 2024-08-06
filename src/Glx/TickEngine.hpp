#pragma once
#include <Singleton.hh>
#include "Logging.hpp"
#include "GlWindow.hpp"
#include "ImGuiBaseFrame.hpp"

namespace Glx
{
class TickEngine
{
public:
    int Initialize()
    {
        Singleton::Get<Logging>().Initialize();
        if (!!Singleton::Get<GlWindow>().Initialize())
            return -1;
        Singleton::Get<ImGuiBaseFrame>().Initialize();

        return 0;
    }

    void PreTick()
    {
        Singleton::Get<GlWindow>().PreTick();
        Singleton::Get<ImGuiBaseFrame>().PreTick();
    }

    void Tick()
    {
        Singleton::Get<ImGuiBaseFrame>().Tick();
    }

    void PostTick()
    {
        Singleton::Get<ImGuiBaseFrame>().PostTick();
        Singleton::Get<GlWindow>().PostTick();
    }

    void Finalize()
    {
        Singleton::Get<ImGuiBaseFrame>().Finalize();
        Singleton::Get<GlWindow>().Finalize();
        Singleton::Get<Logging>().Finalize();
    }

    void Run()
    {
        Initialize();
        while (!glfwWindowShouldClose(Singleton::Get<GlWindow>().GlfwWindowPtr))
        {
            PreTick();
            Tick();
            PostTick();
        }
        Finalize();
    }
};
} // namespace Glx