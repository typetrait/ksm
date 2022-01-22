#pragma once

#include <Kreckanism/Kreckanism.h>

class Debug
{
public:
    static void Init(GLFWwindow* window);
    static void Update();
    static void Render();
    static void Shutdown();
};
