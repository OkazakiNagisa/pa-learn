#pragma once
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Glx/Interfaces/Initializable.h>
#include <Glx/Interfaces/Tickable.h>

namespace Glx
{
class GlWindow : public virtual Interfaces::Virtual::Initializable,
                 public virtual Interfaces::Virtual::Tickable
{
public:
    const int InitOrder = 1;

    void Initialize() override
    {
        if (Initialized)
            return;

        glfwSetErrorCallback([](int error, const char *description) {
            spdlog::error("GLFW Error {}: {}", error, description);
        });
        if (!glfwInit())
        {
            spdlog::error("glfwInit Error!");
            return;
        }

        // GL 3.0 + GLSL 130
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window with graphics context
        window = glfwCreateWindow(Width, Height, "Dear ImGui GLFW+OpenGL3 example",
                                  nullptr, nullptr);
        if (window == nullptr)
        {
            spdlog::error("glfwCreateWindow Error!");
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            spdlog::error("gladLoadGLLoader failed");
            glfwDestroyWindow(window);
            glfwTerminate();
            return;
        }

        Initialized = true;
    }
    void Finalize() override
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLFWwindow *GetWindow()
    {
        return window;
    }

private:
    GLFWwindow *window;
    int Width = 800;
    int Height = 600;
};
} // namespace Glx