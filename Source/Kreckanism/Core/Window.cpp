#include "Kreckanism/Core/Window.h"

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Kreckanism/Core/Log.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

namespace Ksm
{
    Window::Window(int width, int height, std::string title) : width(width), height(height), title(title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        KLOG_INFO("info");
        KLOG_WARN("warn");
        KLOG_FAIL("fail");

        if (window == NULL)
        {
            KLOG_FAIL("fail");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            KLOG_FAIL("fail");
            glfwTerminate();
            return;
        }

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    Window::~Window()
    {

    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(window);
    }
}
