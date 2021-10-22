#include "Demo/Demo.h"

#include <sstream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <Kreckanism/Input/Input.h>
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
#include <Kreckanism/Render/Renderer.h>
#include <Kreckanism/Render/Mesh.h>

void Demo::Startup()
{
    window = new Ksm::Window(800, 600, "Krecka");
    window->SetEventCallback([this](Ksm::Event& e)
    {
        OnEvent(e);
    });

    Ksm::Input::Initialize(window->GetWindow());

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

    auto triangle = Ksm::Mesh::CreateTriangle(1.0f);
    auto quad = Ksm::Mesh::CreateQuad(1.0f, 1.0f);
    auto cube = Ksm::Mesh::CreateCube(1.0f);

    const Ksm::Shader basicShader("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    basicShader.Bind();

    Ksm::PerspectiveCamera camera(65.0f, 800.0f / 600.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 model2 = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
    glm::mat4 model3 = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));

    while (!window->ShouldClose())
    {
        Ksm::Renderer::Clear({ 0.2f, 0.5f, 0.6f, 1.0f });

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            static float f = 0.0f;

            ImGui::Begin("Krecka Hax v1.0");

            ImGui::Text("Grakour DESTROYER");
            ImGui::SliderFloat("Amount", &f, 0.0f, 360.0f);

            ImGui::Button("Destroy");

            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();
        }

        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::W))
        {
            camera.SetPosition(camera.GetPosition() + camera.GetForward() * 0.02f);
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::S))
        {
            camera.SetPosition(camera.GetPosition() - camera.GetForward() * 0.02f);
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::A))
        {
            camera.SetPosition(camera.GetPosition() - camera.GetRight() * 0.02f);
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::D))
        {
            camera.SetPosition(camera.GetPosition() + camera.GetRight() * 0.02f);
        }

        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Up))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model2 = glm::rotate(model2, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model3 = glm::rotate(model3, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Down))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            model2 = glm::rotate(model2, glm::radians(5.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            model3 = glm::rotate(model3, glm::radians(5.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Left))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model2 = glm::rotate(model2, glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model3 = glm::rotate(model3, glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Right))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model2 = glm::rotate(model2, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model3 = glm::rotate(model3, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        basicShader.Bind();
        basicShader.SetUniform("projection", camera.GetProjectionMatrix());
        basicShader.SetUniform("view", camera.GetViewMatrix());
        basicShader.SetUniform("model", model2);

        Ksm::Renderer::DrawIndexed(triangle->GetVertexArray());

        basicShader.SetUniform("model", model);

        Ksm::Renderer::DrawIndexed(quad->GetVertexArray());

        basicShader.SetUniform("model", model3);

        Ksm::Renderer::DrawIndexed(cube->GetVertexArray());

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
