#include "Kreckanism/Core/Window.h"

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Kreckanism/Core/Logger.h"

namespace Ksm
{
    Window::Window(int width, int height, std::string title) : width(width), height(height), title(title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        if (window == NULL)
        {
            KLOG_FAIL("Failed to create window.");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            KLOG_FAIL("Failed to load GLAD.");
            glfwTerminate();
            return;
        }

        glViewport(0, 0, 800, 600);

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            KLOG_INFO("key event!");
        });

        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}
