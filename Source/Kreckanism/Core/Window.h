#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ksm
{
    class Window
    {
    public:
        Window(int, int, std::string);
        ~Window();
        bool ShouldClose();
        void SwapBuffers();
    private:
        int width;
        int height;
        std::string title;
        GLFWwindow* window;
    };
}
