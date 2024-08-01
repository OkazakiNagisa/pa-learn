#pragma once
#include <string>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Glx
{
namespace GlWindow
{
inline GLFWwindow *GlfwWindowPtr;
inline int Width = 800;
inline int Height = 600;
inline std::string Title = "Demo";

inline int Initialize()
{
    glfwSetErrorCallback([](int error, const char *description) {
        spdlog::error("GLFW Error {}: {}", error, description);
    });
    if (!glfwInit())
    {
        spdlog::error("glfwInit Error!");
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
        spdlog::error("glfwCreateWindow Error!");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(GlfwWindowPtr);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::error("gladLoadGLLoader failed");
        glfwDestroyWindow(GlfwWindowPtr);
        glfwTerminate();
        return -1;
    }

    return 0;
}

void Finalize()
{
    glfwDestroyWindow(GlfwWindowPtr);
    glfwTerminate();
}

inline void PreTick()
{
    glfwPollEvents();
    glfwGetFramebufferSize(GlfwWindowPtr, &Width, &Height);
    glViewport(0, 0, Width, Height);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace GlWindow
} // namespace Glx