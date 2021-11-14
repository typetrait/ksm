#pragma once

#include <Kreckanism/Core/KeyCode.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Ksm
{
    class Input
    {
    public:
        static void Initialize(GLFWwindow* target);
        static bool IsKeyPressed(KeyCode key);
        static glm::vec2 GetMousePosition();
    private:
        inline static GLFWwindow* window = nullptr;
    };
}
