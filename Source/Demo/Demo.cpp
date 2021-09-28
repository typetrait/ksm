#include "Demo/Demo.h"

void Demo::Startup()
{
    window = new Ksm::Window(800, 600, "Krecka");
}

void Demo::Run()
{
    while (!window->ShouldClose())
    {
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window->Update();
    }
}

void Demo::Exit()
{
    delete window;
}
