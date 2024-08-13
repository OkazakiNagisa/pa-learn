#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Singleton.hh>
#include "GlWindow.hh"
#include "ImGuiFrameContent/Main.hh"
#include "ImGuiFrameContent/DebugHud.hh"

namespace Glx
{
class ImGuiBaseFrame
{
public:
    void Initialize()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so
        // platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const char *glsl_version = "#version 130";
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(Singleton::Get<Glx::GlWindow>().GlfwWindowPtr, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void PreTick()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Tick()
    {
        Singleton::Get<ImGuiFrameContent::Main>().Tick();
        Singleton::Get<ImGuiFrameContent::DebugHud>().Tick();
    }

    void PostTick()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we
        // save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call
        //  glfwMakeContextCurrent(window) directly)
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void Finalize()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};
} // namespace Glx