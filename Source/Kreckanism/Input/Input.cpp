#include <Kreckanism/Input/Input.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Ksm
{
    void Input::Initialize(GLFWwindow* target)
    {
        window = target;
    }

    bool Input::IsKeyPressed(KeyCode key)
    {
        int state = glfwGetKey(window, key);
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        double x = 0.0, y = 0.0;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(x, y);
    }
}
