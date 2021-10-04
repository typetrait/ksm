#include "Demo/Demo.h"

#include <sstream>

#include "glm/glm.hpp"

#include "Kreckanism/Event/WindowResizeEvent.h"
#include "Kreckanism/Event/KeyPressedEvent.h"
#include "Kreckanism/Event/EventDispatcher.h"
#include "Kreckanism/Graphics/IndexBuffer.h"
#include "Kreckanism/Graphics/Shader.h"
#include "Kreckanism/Graphics/VertexBuffer.h"

void Demo::Startup()
{
    window = new Ksm::Window(800, 600, "Krecka");
    window->SetEventCallback([this](Ksm::Event& e)
    {
        OnEvent(e);
    });

    std::stringstream fmt;
    fmt << "GL Info: " << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << "(" << glGetString(GL_VERSION) << ")";
    KLOG_INFO(fmt.str());
}

void Demo::Run()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2, 2, 3, 0
    };

    const Ksm::VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.Bind();

    const Ksm::IndexBuffer ibo(indices, 6);
    ibo.Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    const Ksm::Shader basic("");
    basic.Use();

    while (!window->ShouldClose())
    {
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window->Update();
    }

    glDeleteVertexArrays(1, &VAO);
}

void Demo::OnEvent(Ksm::Event& e)
{
    Ksm::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Ksm::WindowResizeEvent>([](const Ksm::WindowResizeEvent& ev)
    {
        std::stringstream fmt;
        fmt << "Window resized: Width=" << ev.GetWidth() << " Height=" << ev.GetHeight();
        KLOG_INFO(fmt.str());
    });

    dispatcher.Dispatch<Ksm::KeyPressedEvent>([](const Ksm::KeyPressedEvent& ev)
    {
        std::stringstream fmt;
        fmt << "Key pressed: KeyCode= " << ev.GetKeyCode();
        KLOG_INFO(fmt.str());
    });
}

void Demo::Exit()
{
    delete window;
}
