#pragma once

#include <Kreckanism/Core/KeyCode.h>

#include <GLFW/glfw3.h>

namespace Ksm
{
    class Input
    {
    public:
        static void Initialize(GLFWwindow* target);
        static bool IsKeyPressed(KeyCode key);
    private:
        inline static GLFWwindow* window = nullptr;
    };
}
