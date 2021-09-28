#include "Kreckanism/Kreckanism.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Kreckanism/Core/Window.h"

namespace Ksm
{
    Kreckanism::Kreckanism()
    {
        Window window(800, 600, "Krecka");

        while (!window.ShouldClose())
        {
            //process_input();
            glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            window.SwapBuffers();
            glfwPollEvents();
            //limit_fps();
        }
        
        glfwTerminate();
        return;
    }

    Kreckanism::~Kreckanism()
    {
    }
}
