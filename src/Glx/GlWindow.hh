#pragma once
#include <string>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Glx
{
class GlWindow
{
public:
    GLFWwindow *GlfwWindowPtr;
    bool VsyncEnabled = false;
    int Width = 800;
    int Height = 600;
    std::string Title = "Demo";
    ImVec4 BackgroundColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    int Initialize()
    {
        glfwSetErrorCallback([](int error, const char *description) {
            LogErr("GLFW Error {}: {}", error, description);
        });
        if (!glfwInit())
        {
            LogErr("glfwInit Error!");
            return -1;
        }

        // GL 3.0 + GLSL 130
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window with graphics context
        GlfwWindowPtr =
            glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
        if (GlfwWindowPtr == nullptr)
        {
            LogErr("glfwCreateWindow Error!");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(GlfwWindowPtr);
        if (VsyncEnabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LogErr("gladLoadGLLoader failed");
            glfwDestroyWindow(GlfwWindowPtr);
            glfwTerminate();
            return -1;
        }

        return 0;
    }

    void PreTick()
    {
        glfwPollEvents();
        glfwGetFramebufferSize(GlfwWindowPtr, &Width, &Height);
        glViewport(0, 0, Width, Height);
        glClearColor(BackgroundColor.x * BackgroundColor.w,
                     BackgroundColor.y * BackgroundColor.w,
                     BackgroundColor.z * BackgroundColor.w, BackgroundColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void PostTick()
    {
        glfwSwapBuffers(GlfwWindowPtr);
    }

    void Finalize()
    {
        glfwDestroyWindow(GlfwWindowPtr);
        glfwTerminate();
    }
};
} // namespace Glx