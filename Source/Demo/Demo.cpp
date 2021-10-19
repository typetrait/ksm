#include "Demo/Demo.h"

#include <sstream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include <Kreckanism/Event/WindowResizeEvent.h>
#include <Kreckanism/Event/KeyPressedEvent.h>
#include <Kreckanism/Event/EventDispatcher.h>
#include <Kreckanism/Render/API/OpenGL/BufferLayout.h>
#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/Shader.h>
#include <Kreckanism/Render/API/OpenGL/VertexArray.h>
#include <Kreckanism/Render/API/OpenGL/VertexBuffer.h>
#include <Kreckanism/Render/Vertex.h>
#include <Kreckanism/Render/PerspectiveCamera.h>

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

    Ksm::VertexArray vertexArray;
    vertexArray.Bind();

    auto vertexBuffer = std::make_shared<Ksm::VertexBuffer>(reinterpret_cast<float*>(vertices), sizeof(vertices));
    vertexBuffer->Bind();

    auto indexBuffer = std::make_shared<Ksm::IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    indexBuffer->Bind();

    Ksm::BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();

    vertexBuffer->SetLayout(layout);

    vertexArray.AddVertexBuffer(vertexBuffer);
    vertexArray.SetIndexBuffer(indexBuffer);

    const Ksm::Shader basicShader("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    basicShader.Bind();

    Ksm::PerspectiveCamera camera;

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
