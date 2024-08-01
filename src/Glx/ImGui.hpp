#pragma once
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Glx/Interfaces/Initializable.h>
#include <Glx/Interfaces/Tickable.h>

namespace Glx
{
class GlWindow : public virtual Interfaces::Virtual::Initializable,
                 public virtual Interfaces::Virtual::Tickable
{
public:
    const int InitOrder = 2;

    void SetWindow(GLFWwindow *window)
    {
        Window = window;
    }

    void Initialize() override
    {
        if (Initialized)
            return;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
        ImGui_ImplGlfw_InitForOpenGL(Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        Initialized = true;
    }
    void Finalize() override
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

private:
    GLFWwindow *Window;
};
} // namespace Glx