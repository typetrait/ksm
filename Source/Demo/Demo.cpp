#include "Demo/Demo.h"

#include <sstream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/glm.hpp"

#include "Kreckanism/Event/WindowResizeEvent.h"
#include "Kreckanism/Event/KeyPressedEvent.h"
#include "Kreckanism/Event/EventDispatcher.h"
#include "Kreckanism/Graphics/BufferLayout.h"
#include "Kreckanism/Graphics/IndexBuffer.h"
#include "Kreckanism/Graphics/Shader.h"
#include "Kreckanism/Graphics/Vertex.h"
#include "Kreckanism/Graphics/VertexArray.h"
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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Ksm::Vertex vertices[] =
    {
        {{ -0.5f, -0.5f, 0.0f }, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f }, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 1.0f}},
        {{ -0.5f, 0.5f, 0.0f }, {1.0f, 1.0f, 1.0f}}
    };

    unsigned int indices[] =
    {
        0, 1, 2, 2, 3, 0
    };

    Ksm::VertexArray vao;
    vao.Bind();

    Ksm::VertexBuffer vbo(reinterpret_cast<float*>(vertices), sizeof(vertices));
    vbo.Bind();

    auto indexBuffer = std::make_shared<Ksm::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    indexBuffer->Bind();

    vao.SetIndexBuffer(indexBuffer);

    Ksm::BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();

    vbo.SetLayout(layout);

    unsigned int stride = layout.GetStride();

    unsigned int index = 0;
    unsigned int offset = 0;
    for (const auto& attribute : layout.GetAttributes())
    {
        glVertexAttribPointer(index, attribute.count, attribute.type, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(index);

        index++;
        offset += attribute.size;
    }

    const Ksm::Shader basic("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    basic.Use();

    while (!window->ShouldClose())
    {
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;

            ImGui::Begin("Krecka Hax v1.0");

            ImGui::Text("Grakour DESTROYER");
            ImGui::SliderFloat("Amount", &f, 0.0f, 1.0f);

            ImGui::Button("Destroy");

            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();
        }

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->Update();
    }
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete window;
}
