#include "Demo/Core/Demo.h"

#include <chrono>
#include <memory>
#include <vector>

#include <fmt/format.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Demo/Core/Debug.h>
#include <Kreckanism/Kreckanism.h>

void Demo::Startup()
{
    window = new Ksm::Window(800, 600, "Krecka");
    window->SetEventCallback([this](Ksm::Event& e)
    {
        OnEvent(e);
    });

    Ksm::Input::Initialize(window->GetWindow());

    KLOG_INFO(fmt::format("Renderer Info: {} | {} | {}.",
        (const char*)glGetString(GL_VENDOR),
        (const char*)glGetString(GL_RENDERER),
        (const char*)glGetString(GL_VERSION)));
}

void Demo::Run()
{
    Debug::Init(window->GetWindow());
    camera = std::make_unique<Ksm::PerspectiveCamera>(65.0f, 800.0f / 600.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 3.0f));

    auto sphere = Ksm::PrimitiveFactory::CreateSphere(1.0f, 36, 18);
    auto cube = Ksm::PrimitiveFactory::CreateCube(1.0f);
    auto quad = Ksm::PrimitiveFactory::CreateQuad(1.0f, 1.0f);
    Ksm::Texture blank("Assets/Textures/blank16x16.png");

    shaders["Light"] = std::make_shared<Ksm::Shader>("Assets/Shaders/Light.vert", "Assets/Shaders/Light.frag");
    shaders["LightCube"] = std::make_shared<Ksm::Shader>("Assets/Shaders/LightCube.vert", "Assets/Shaders/LightCube.frag");

    lightPos = glm::vec3(-2.0f, 0.0f, -1.0f);
    lightPos2 = glm::vec3(0.0f, 2.0f, 0.0f);
    models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    models["Sphere1"] = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f));
    models["Sphere2"] = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
    models["Cube"] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 8.0f, 3.0f));
    models["Sphere3"] = glm::translate(glm::mat4(1.0f), lightPos2);
    models["Cube3"] = glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, -1.5f, 0.0f));

    models["Quad"] = glm::scale(glm::rotate(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)),
        glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        glm::vec3(40.0f, 40.0f, 1.0f));

    models["Cube2"] = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)), glm::vec3(40.0f, 1.0f, 40.0f));

    materials["Green"] = {{0.3f, 1.0f, 0.3f}, {0.3f, 1.0f, 0.3f}, {0.5f, 0.5f, 0.5f}, 128.0f};
    materials["Blue"] = {{0.3f, 0.3f, 1.0f}, {0.3f, 0.3f, 1.0f}, {0.5f, 0.5f, 0.5f}, 32.0f};
    materials["Sand"] = {{0.3f, 0.3f, 0.3f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 32.0f};

    // Shadows
    shaders["Depth"] = std::make_shared<Ksm::Shader>("Assets/Shaders/Depth.vert", "Assets/Shaders/Depth.frag");
    shaders["DebugDepthMap"] = std::make_shared<Ksm::Shader>("Assets/Shaders/DebugDepthMap.vert", "Assets/Shaders/DebugDepthMap.frag");

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Ksm::DeltaTime deltaTime;
    while (!window->ShouldClose())
    {
        // Update
        Debug::Update();
        deltaTime.Update();
        OnUpdate(deltaTime.Get());
        Ksm::Renderer::Clear({ 0.0f, 0.7f, 0.9f, 1.0f });

        // Shadows (Calculate Depth Map)
        float nearPlane = 1.0f, farPlane = 15.0f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
        glm::mat4 lightView = glm::lookAt(lightPos2, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        shaders["Depth"]->Bind();
        shaders["Depth"]->SetUniform("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        shaders["Depth"]->SetUniform("model", models["Sphere1"]);
        Ksm::Renderer::DrawIndexed(sphere->GetVertexArray());
        shaders["Depth"]->SetUniform("model", models["Sphere2"]);
        Ksm::Renderer::DrawIndexed(sphere->GetVertexArray());
        shaders["Depth"]->SetUniform("model", models["Quad"]);
        Ksm::Renderer::DrawIndexed(quad->GetVertexArray());
        shaders["Depth"]->SetUniform("model", models["Cube"]);
        Ksm::Renderer::DrawIndexed(cube->GetVertexArray());
        shaders["Depth"]->SetUniform("model", models["Cube3"]);
        Ksm::Renderer::DrawIndexed(cube->GetVertexArray());
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // DepthMap Texture Quad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaders["DebugDepthMap"]->Bind();
        shaders["DebugDepthMap"]->SetUniform("nearPlane", nearPlane);
        shaders["DebugDepthMap"]->SetUniform("farPlane", farPlane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        Ksm::Renderer::DrawIndexed(quad->GetVertexArray());
        glBindTexture(GL_TEXTURE_2D, 0);

        glViewport(0, 0, window->GetWidth(), window->GetHeight());

        // Light cube
        shaders["LightCube"]->Bind();
        shaders["LightCube"]->SetUniform("projection", camera->GetProjectionMatrix());
        shaders["LightCube"]->SetUniform("view", camera->GetViewMatrix());
        shaders["LightCube"]->SetUniform("model", models["LightCube"]);
        Ksm::Renderer::DrawIndexed(cube->GetVertexArray());

        // Objects
        blank.Bind();
        shaders["Light"]->Bind();
        shaders["Light"]->SetUniform("projection", camera->GetProjectionMatrix());
        shaders["Light"]->SetUniform("view", camera->GetViewMatrix());
        shaders["Light"]->SetUniform("viewPos", camera->GetPosition());
        shaders["Light"]->SetUniform("lightSpaceMatrix", lightSpaceMatrix);
        shaders["Light"]->SetUniform("sampler", 0);
        shaders["Light"]->SetUniform("shadowMap", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        shaders["Light"]->SetUniform("directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shaders["Light"]->SetUniform("directionalLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
        shaders["Light"]->SetUniform("directionalLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shaders["Light"]->SetUniform("directionalLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        shaders["Light"]->SetUniform("pointLight.position", lightPos);
        shaders["Light"]->SetUniform("pointLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        shaders["Light"]->SetUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        shaders["Light"]->SetUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shaders["Light"]->SetUniform("pointLight.constant", 1.0f);
        shaders["Light"]->SetUniform("pointLight.linear", 0.09f);
        shaders["Light"]->SetUniform("pointLight.quadratic", 0.032f);

        shaders["Light"]->SetUniform("spotLight.position", camera->GetPosition());
        shaders["Light"]->SetUniform("spotLight.direction", camera->GetForward());
        shaders["Light"]->SetUniform("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        shaders["Light"]->SetUniform("spotLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        shaders["Light"]->SetUniform("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shaders["Light"]->SetUniform("spotLight.constant", 1.0f);
        shaders["Light"]->SetUniform("spotLight.linear", 0.09f);
        shaders["Light"]->SetUniform("spotLight.quadratic", 0.032f);
        shaders["Light"]->SetUniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shaders["Light"]->SetUniform("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

        shaders["Light"]->SetUniform("material.ambient", materials["Blue"].ambient);
        shaders["Light"]->SetUniform("material.diffuse", materials["Blue"].diffuse);
        shaders["Light"]->SetUniform("material.specular", materials["Blue"].specular);
        shaders["Light"]->SetUniform("material.shininess", materials["Blue"].shininess);

        shaders["Light"]->SetUniform("model", models["Sphere1"]);
        shaders["Light"]->SetUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(models["Sphere1"]))));
        Ksm::Renderer::DrawIndexed(sphere->GetVertexArray());

        shaders["Light"]->SetUniform("model", models["Sphere2"]);
        shaders["Light"]->SetUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(models["Sphere2"]))));
        Ksm::Renderer::DrawIndexed(sphere->GetVertexArray());

        shaders["Light"]->SetUniform("model", models["Cube"]);
        shaders["Light"]->SetUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(models["Cube"]))));
        Ksm::Renderer::DrawIndexed(cube->GetVertexArray());

        shaders["Light"]->SetUniform("model", models["Sphere3"]);
        shaders["Light"]->SetUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(models["Sphere3"]))));
        Ksm::Renderer::DrawIndexed(sphere->GetVertexArray());

        shaders["Light"]->SetUniform("model", models["Cube3"]);
        shaders["Light"]->SetUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(models["Cube3"]))));
        Ksm::Renderer::DrawIndexed(cube->GetVertexArray());

        shaders["Light"]->SetUniform("material.ambient", materials["Sand"].ambient);
        shaders["Light"]->SetUniform("material.diffuse", materials["Sand"].diffuse);
        shaders["Light"]->SetUniform("material.specular", materials["Sand"].specular);
        shaders["Light"]->SetUniform("material.shininess", materials["Sand"].shininess);

        shaders["Light"]->SetUniform("model", models["Quad"]);
        shaders["Light"]->SetUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(models["Quad"]))));
        Ksm::Renderer::DrawIndexed(quad->GetVertexArray());

        glBindTexture(GL_TEXTURE_2D, 0);

        // Update
        Debug::Render();
        window->Update();
    }
}

void Demo::Exit()
{
    Debug::Shutdown();
    delete window;
}

void Demo::OnUpdate(double deltaTime)
{
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::W))
    {
        camera->SetPosition(camera->GetPosition() + camera->GetForward() * (float)(2.0f * deltaTime));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::S))
    {
        camera->SetPosition(camera->GetPosition() - camera->GetForward() * (float)(2.0f * deltaTime));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::A))
    {
        camera->SetPosition(camera->GetPosition() - camera->GetRight() * (float)(2.0f * deltaTime));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::D))
    {
        camera->SetPosition(camera->GetPosition() + camera->GetRight() * (float)(2.0f * deltaTime));
    }

    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Y))
    {
        lightPos = glm::vec3(lightPos.x, lightPos.y + 1.0*deltaTime, lightPos.z);
        models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::J))
    {
        lightPos = glm::vec3(lightPos.x - 1.0*deltaTime, lightPos.y, lightPos.z);
        models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::H))
    {
        lightPos = glm::vec3(lightPos.x, lightPos.y - 1.0*deltaTime, lightPos.z);
        models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::L))
    {
        lightPos = glm::vec3(lightPos.x + 1.0*deltaTime, lightPos.y, lightPos.z);
        models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::I))
    {
        lightPos = glm::vec3(lightPos.x, lightPos.y, lightPos.z - 1.0*deltaTime);
        models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::K))
    {
        lightPos = glm::vec3(lightPos.x, lightPos.y, lightPos.z + 1.0*deltaTime);
        models["LightCube"] = glm::translate(glm::mat4(1.0f), lightPos);
    }

    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Up))
    {
        lightPos2 = glm::vec3(lightPos2.x, lightPos2.y, lightPos2.z - 1.0*deltaTime);
        models["Sphere3"] = glm::translate(glm::mat4(1.0f), lightPos2);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Down))
    {
        lightPos2 = glm::vec3(lightPos2.x, lightPos2.y, lightPos2.z + 1.0*deltaTime);
        models["Sphere3"] = glm::translate(glm::mat4(1.0f), lightPos2);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Left))
    {
        lightPos2 = glm::vec3(lightPos2.x - 1.0*deltaTime, lightPos2.y, lightPos2.z);
        models["Sphere3"] = glm::translate(glm::mat4(1.0f), lightPos2);
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Right))
    {
        lightPos2 = glm::vec3(lightPos2.x + 1.0*deltaTime, lightPos2.y, lightPos2.z);
        models["Sphere3"] = glm::translate(glm::mat4(1.0f), lightPos2);
    }
}

void Demo::OnWindowResize(const Ksm::WindowResizeEvent& ev)
{
    window->SetWidth(ev.GetWidth());
    window->SetHeight(ev.GetHeight());
    camera->SetAspectRatio(ev.GetWidth() / (float)ev.GetHeight());
}
