#include "Demo/Demo.h"

#include <format>
#include <chrono>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <Kreckanism/Input/Input.h>
#include <Kreckanism/Event/WindowResizeEvent.h>
#include <Kreckanism/Event/KeyPressedEvent.h>
#include <Kreckanism/Event/MouseMoveEvent.h>
#include <Kreckanism/Event/MousePressedEvent.h>
#include <Kreckanism/Event/MouseReleasedEvent.h>
#include <Kreckanism/Event/EventDispatcher.h>
#include <Kreckanism/Render/API/OpenGL/BufferLayout.h>
#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/VertexArray.h>
#include <Kreckanism/Render/API/OpenGL/VertexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/Shader.h>
#include <Kreckanism/Render/API/OpenGL/Texture.h>
#include <Kreckanism/Render/Vertex.h>
#include <Kreckanism/Render/PerspectiveCamera.h>
#include <Kreckanism/Render/Renderer.h>
#include <Kreckanism/Render/Mesh.h>
#include <Kreckanism/Scene/FbxLoader.h>

void Demo::Startup()
{
    window = new Ksm::Window(800, 600, "Krecka");
    window->SetEventCallback([this](Ksm::Event& e)
    {
        OnEvent(e);
    });

    Ksm::Input::Initialize(window->GetWindow());

    KLOG_INFO(std::format("Renderer Info: {} | {} | {}.", (const char*)glGetString(GL_VENDOR),
                                                          (const char*)glGetString(GL_RENDERER),
                                                          (const char*)glGetString(GL_VERSION)));
}

void Demo::Run()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Ksm::FbxLoader loader;
    auto bunnyMeshes = loader.LoadMesh("Assets/Models/Bunny/Bunny.fbx");

    Ksm::Texture forbidden("Assets/Textures/forbidden.png");

    const Ksm::Shader basicShader("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    basicShader.Bind();

    Ksm::PerspectiveCamera camera(65.0f, 800.0f / 600.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));

    while (!window->ShouldClose())
    {
        Ksm::Renderer::Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug");

        ImGui::Text("Runtime Statistics:");
        ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

        ImGui::Text("Cursor Pos: x=%.1f y=%.1f", Ksm::Input::GetMousePosition().x, Ksm::Input::GetMousePosition().y);

        ImGui::End();

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
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Down))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Left))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        }
        if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Right))
        {
            model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        basicShader.Bind();
        basicShader.SetUniform("projection", camera.GetProjectionMatrix());
        basicShader.SetUniform("view", camera.GetViewMatrix());
        basicShader.SetUniform("model", model);

        forbidden.Bind();

        for (auto& mesh : bunnyMeshes)
        {
            Ksm::Renderer::DrawIndexed(mesh.GetVertexArray());
        }

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
        KLOG_INFO(std::format("Window resized: Width={}, Height={}.", ev.GetWidth(), ev.GetHeight()));
    });

    dispatcher.Dispatch<Ksm::KeyPressedEvent>([](const Ksm::KeyPressedEvent& ev)
    {
        KLOG_INFO(std::format("Key pressed: KeyCode={}.", ev.GetKeyCode()));
    });

    dispatcher.Dispatch<Ksm::MouseMoveEvent>([](const Ksm::MouseMoveEvent& ev)
    {
        KLOG_INFO(std::format("Mouse moved: X={}, Y={}.", ev.GetX(), ev.GetY()));
    });

    dispatcher.Dispatch<Ksm::MousePressedEvent>([](const Ksm::MousePressedEvent& ev)
    {
        KLOG_INFO(std::format("Mouse pressed: Button={}.", ev.GetButton()));
    });

    dispatcher.Dispatch<Ksm::MouseReleasedEvent>([](const Ksm::MouseReleasedEvent& ev)
    {
        KLOG_INFO(std::format("Mouse released: Button={}.", ev.GetButton()));
    });
}

void Demo::Exit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete window;
}
