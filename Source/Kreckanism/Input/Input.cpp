#include <Kreckanism/Input/Input.h>

#include <GLFW/glfw3.h>

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
}
