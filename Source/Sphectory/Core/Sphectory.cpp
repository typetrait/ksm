#include <Sphectory/Core/Sphectory.h>

#include <chrono>
#include <memory>
#include <vector>
#include <limits>

#include <fmt/format.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/intersect.hpp>

#include <Kreckanism/Audio/AudioEngine.h>
#include <Kreckanism/Kreckanism.h>

#include <Sphectory/Core/Debug.h>
#include <Sphectory/Core/AssetManager.h>
#include <Sphectory/Render/Icosphere.h>
#include <Sphectory/State/InGameState.h>
#include <Sphectory/State/State.h>
#include <Sphectory/Render/GeometryShader.h>

constexpr int SELECTION_MAX = 20;

void Sphectory::Startup()
{
    window = new Ksm::Window(800, 600, "Sphectory");
    window->SetEventCallback([this](Ksm::Event& e)
    {
        OnEvent(e);
    });

    Ksm::Input::Initialize(window->GetWindow());
    Ksm::AudioEngine::Initialize();

    KLOG_INFO(fmt::format("Renderer Info: {} | {} | {}.",
        (const char*)glGetString(GL_VENDOR),
        (const char*)glGetString(GL_RENDERER),
        (const char*)glGetString(GL_VERSION)));
}

void Sphectory::Run()
{
    Debug::Init(window->GetWindow());
    camera = std::make_unique<Ksm::PerspectiveCamera>(65.0f, 800.0f / 600.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 16.0f));

    inGameState = std::make_shared<InGameState>();

    Ksm::Transform transform({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(90.0f) });
    //std::shared_ptr<Ksm::Mesh> cube = Ksm::PrimitiveFactory::CreateCube(1.0f);
    //std::vector<Ksm::Mesh> meshes({ *cube });
    //std::shared_ptr<Ksm::Mesh> sphere = Ksm::PrimitiveFactory::CreateSphere(1.0f, 36, 18);
    Icosphere ico(8.0f, 2, false);
    auto sphere = ico.GetMesh();
    std::vector<Ksm::Mesh> meshes({ *sphere });
    //auto meshes = AssetManager::LoadMeshes("Assets/Models/Bunny/Bunny.fbx");
    std::shared_ptr<Ksm::Texture> texture = AssetManager::LoadTexture("Assets/Textures/earth.png", false);
    Entity e(transform, meshes, texture, inGameState);
    inGameState->AddEntity(e);

    shaders["Planet"] = std::make_shared<Ksm::Shader>("Assets/Shaders/Planet.vert", "Assets/Shaders/Planet.frag");
    shaders["PlanetConsume"] = std::make_shared<Ksm::Shader>("Assets/Shaders/PlanetConsume.vert", "Assets/Shaders/PlanetConsume.frag");
    shaders["PlanetBasic"] = std::make_shared<Ksm::Shader>("Assets/Shaders/PlanetBasic.vert", "Assets/Shaders/PlanetBasic.frag");

    //shaders["Geometry"] = std::make_shared<GeometryShader>("Assets/Shaders/Geo.vert", "Assets/Shaders/Geo.frag", "Assets/Shaders/Geo.geom");
    //shaders["Geometry"] = std::make_shared<Ksm::Shader>("Assets/Shaders/Geo.vert", "Assets/Shaders/Geo.frag");
    shaders["GeoConsume"] = std::make_shared<GeometryShader>(
        "Assets/Shaders/GeoConsume.vert",
        "Assets/Shaders/GeoConsume.frag",
        "Assets/Shaders/GeoConsume.geom"
    );

    Ksm::AudioEngine::LoadSound("Assets/Audio/standrews.wav");
    Ksm::AudioEngine::LoadSound("Assets/Audio/background.wav");
    //Ksm::AudioEngine::PlaySound("Assets/Audio/background.wav", glm::vec3(0.0f), 1.0f);

    Ksm::DeltaTime deltaTime;
    while (!window->ShouldClose())
    {
        // Update
        Debug::Update();
        deltaTime.Update();
        OnUpdate(deltaTime.Get());
        Ksm::Renderer::Clear({ 0.0f, 0.7f, 0.9f, 1.0f });
        glViewport(0, 0, window->GetWidth(), window->GetHeight());

        // Entities
        auto shader = shaders["GeoConsume"];
        shader->Bind();
        shader->SetUniform("projection", camera->GetProjectionMatrix());
        shader->SetUniform("view", camera->GetViewMatrix());
        shader->SetUniform("viewPos", camera->GetPosition());

        /* Planet.frag / Planet.vert */
        /*
        int selectedIndices[SELECTION_MAX];
        for (int i=0; i<SELECTION_MAX; ++i) // TODO: only from number of selected to max
            selectedIndices[i] = -1;
        int i=0;
        for (auto clickInfo : meshClicks) {
            selectedIndices[i] = (int)clickInfo.second.entityMeshIndex;
            i++;
            if (i > SELECTION_MAX - 1)
                break;
        }
        shader->SetUniform("selectedIndices", selectedIndices, SELECTION_MAX);
        */

        /* PlanetConsume.frag / PlanetConsume.vert */
        /* */
        int selectedVertices[(SELECTION_MAX * 3)];
        for (int i=0; i < (SELECTION_MAX * 3); ++i) // TODO: only from number of selected to max
            selectedVertices[i] = -1;

        auto planet = inGameState->GetEntities()[0].GetMeshes()[0];
        auto planetIndices = planet.GetIndices();

        int i=0;
        for (auto clickInfo : meshClicks) {
            int index = (int)clickInfo.second.entityMeshIndex;
            selectedVertices[i] = planetIndices[index*3];
            selectedVertices[i+1] = planetIndices[index*3+1];
            selectedVertices[i+2] = planetIndices[index*3+2];
            i += 3;
            if (i > (SELECTION_MAX - 1) * 3)
                break;
        }
        shader->SetUniform("selectedVertices", selectedVertices, (SELECTION_MAX * 3));
        /* */

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /*
        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            */
        //glEnable(GL_CULL_FACE);
        glActiveTexture(GL_TEXTURE1);
        for (auto entity : inGameState->GetEntities()) {
            entity.BindTexture();
            shader->SetUniform("model", entity.GetModel());
            for (auto mesh : entity.GetMeshes()) {
                Ksm::Renderer::DrawIndexed(mesh.GetVertexArray());
            }
        }

        // Update
        Debug::Render();
        window->Update();

        Ksm::AudioEngine::Update();
    }
}

void Sphectory::Exit()
{
    Debug::Shutdown();
    Ksm::AudioEngine::Shutdown();
    delete window;
}

void Sphectory::OnUpdate(double deltaTime)
{
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::W))
    {
        camera->SetPosition(camera->GetPosition() + camera->GetForward() * (float)(5.0f * deltaTime));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::S))
    {
        camera->SetPosition(camera->GetPosition() - camera->GetForward() * (float)(5.0f * deltaTime));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::A))
    {
        camera->SetPosition(camera->GetPosition() - camera->GetRight() * (float)(5.0f * deltaTime));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::D))
    {
        camera->SetPosition(camera->GetPosition() + camera->GetRight() * (float)(5.0f * deltaTime));
    }

    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Q))
    {
        wireframe = !wireframe;
    }

    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Up))
    {
        //models["Sphere"] = glm::rotate(models["Sphere"], glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //Ksm::AudioEngine::PlaySound("Assets/Audio/standrews.wav", glm::vec3(0.0f), 1.0f);
        inGameState->TranslateEntity(0, glm::vec3(0.0f, 1.0f * deltaTime, 0.0f));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Down))
    {
        //models["Sphere"] = glm::rotate(models["Sphere"], glm::radians(15.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        //Ksm::AudioEngine::PlaySound("Assets/Audio/standrews.wav", glm::vec3(0.0f), 1.0f);
        inGameState->TranslateEntity(0, glm::vec3(0.0f, -1.0f * deltaTime, 0.0f));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Left))
    {
        //models["Sphere"] = glm::rotate(models["Sphere"], glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //Ksm::AudioEngine::PlaySound("Assets/Audio/standrews.wav", glm::vec3(0.0f), 1.0f);
        inGameState->TranslateEntity(0, glm::vec3(-1.0f * deltaTime, 0.0f, 0.0f));
    }
    if (Ksm::Input::IsKeyPressed(Ksm::KeyCode::Right))
    {
        //models["Sphere"] = glm::rotate(models["Sphere"], glm::radians(15.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        //Ksm::AudioEngine::PlaySound("Assets/Audio/standrews.wav", glm::vec3(0.0f), 1.0f);
        inGameState->TranslateEntity(0, glm::vec3(1.0f * deltaTime, 0.0f, 0.0f));
    }
}

void Sphectory::OnWindowResize(const Ksm::WindowResizeEvent& ev)
{
    window->SetWidth(ev.GetWidth());
    window->SetHeight(ev.GetHeight());
    camera->SetAspectRatio(ev.GetWidth() / (float)ev.GetHeight());
}

void Sphectory::OnMouseMove(const Ksm::MouseMoveEvent& ev)
{
    if (this->isDragging)
    {
        auto currentPosition = glm::vec2(ev.GetX(), ev.GetY());
        this->MouseDragDelta = currentPosition - MouseDragPrevious;
        this->MouseDragPrevious = currentPosition;
        MouseDragDistance = glm::length(MouseDragDelta);
        camera->Update(MouseDragDelta);
    }
}

glm::vec3 Sphectory::CalcRayDirection(glm::vec2 mousePosition)
{
    glm::vec3 rayNDC((2.0f * mousePosition.x) / window->GetWidth() - 1.0f,
        1.0f - ((2.0f * mousePosition.y) / window->GetHeight()),
        1.0f
    );

    glm::vec4 rayClip = glm::vec4(rayNDC.x, rayNDC.y, -1.0f, 1.0f);

    glm::vec4 rayEye = glm::inverse(camera->GetProjectionMatrix()) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    glm::vec3 rayWorld(glm::inverse(camera->GetViewMatrix()) * rayEye);
    rayWorld = glm::normalize(rayWorld);

    return rayWorld;
}

bool Sphectory::IntersectRayMesh(
    glm::vec3 rayOrigin,
    glm::vec3 rayDir,
    Ksm::Mesh mesh,
    unsigned int& intersectMeshIndex,
    glm::vec2& intersectPos,
    float& intersectDistance)
{
    auto vertices = mesh.GetVertices();
    auto indices = mesh.GetIndices();
    bool intersected = false;
    float closestDistance = std::numeric_limits<float>::max();

    for (int i=0; i < indices.size(); i+=3)
    {
        glm::vec2 pos;
        float distance;

        auto wasClickOnTriangle = glm::intersectRayTriangle(
            rayOrigin,
            rayDir,
            vertices[indices[i]].Position,
            vertices[indices[i+1]].Position,
            vertices[indices[i+2]].Position,
            pos,
            distance
        );

        if (distance < 0)
            distance = -distance;

        if (wasClickOnTriangle && distance < closestDistance)
        {
            intersected = true;
            intersectMeshIndex = i;
            intersectPos = pos;
            intersectDistance = distance;
            closestDistance = distance;
        }

        /*
        if (wasClickOnTriangle)
        {
            intersectMeshIndex = i;
            intersectPos = pos;
            intersectDistance = distance;
            KLOG_WARN(fmt::format("-------- i = {} -------", i));
            KLOG_WARN(fmt::format("{}, {}, {}",
                vertices[indices[i]].Position.x,
                vertices[indices[i]].Position.y,
                vertices[indices[i]].Position.z
            ));
            KLOG_WARN(fmt::format("{}, {}, {}",
                vertices[indices[i+1]].Position.x,
                vertices[indices[i+1]].Position.y,
                vertices[indices[i+1]].Position.z
            ));
            KLOG_WARN(fmt::format("{}, {}, {}",
                vertices[indices[i+2]].Position.x,
                vertices[indices[i+2]].Position.y,
                vertices[indices[i+2]].Position.z
            ));
            KLOG_WARN(fmt::format("{}, {}, {}",
                camera->GetPosition().x,
                camera->GetPosition().y,
                camera->GetPosition().z
            ));
            KLOG_WARN("--------");
            return true;
        }
        */
    }
    return intersected;
}

void Sphectory::OnMousePress(const Ksm::MousePressEvent& ev)
{
    glm::vec2 mousePosition = Ksm::Input::GetMousePosition();
    if (ev.GetButton() == GLFW_MOUSE_BUTTON_LEFT)
    {
        this->isDragging = true;
        this->MouseDragPrevious = mousePosition;
        glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // raycasting
    if (ev.GetButton() == GLFW_MOUSE_BUTTON_RIGHT)
    {
        glm::vec3 rayDirection = CalcRayDirection(mousePosition);

        bool clickedEntity = false;
        int entityIndex = 0;
        unsigned int entityMeshIndex;
        glm::vec2 entityPos;
        float entityDistance = std::numeric_limits<float>::max();

        auto entities = inGameState->GetEntities();
        for (int i=0; i < entities.size(); ++i)
        {
            if (!entities[i].isSelectable())
                continue;

            unsigned int meshIndex;
            glm::vec2 pos;
            float distance;

            auto entityModelInv = glm::inverse(entities[i].GetModel());
            //glm::vec4 tOri = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 0.0f)) * glm::vec4(camera->GetPosition(), 1.0f);
            //glm::vec4 tDir = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 0.0f)) * glm::vec4(rayDirection, 0.0f);
            //auto rayDirectionTransformed = rayDirection;
            //auto rayOriginTransformed = camera->GetPosition();
            //glm::vec3 rayOriginTransformed = glm::vec3(tOri.x, tOri.y, tOri.z);
            //glm::vec3 rayDirectionTransformed = glm::vec3(tDir.x, tDir.y, tDir.z);
            auto rayDirectionTransformed = entityModelInv * glm::vec4(rayDirection, 0.0f);
            auto rayOriginTransformed = entityModelInv * glm::vec4(camera->GetPosition(), 1.0f);

            bool wasClickOnMesh = IntersectRayMesh(
                rayOriginTransformed,
                rayDirectionTransformed,
                entities[i].GetMeshes()[0], // TODO: check all meshes of the entity
                meshIndex,
                pos,
                distance
            );

            if (distance < 0)
                distance = -distance;

            if (wasClickOnMesh && distance < entityDistance) {
                clickedEntity = true;
                entityIndex = i;
                entityDistance = distance;
                entityMeshIndex = meshIndex;
                entityPos = pos;
            }

            /*
            Ksm::Transform transform({ rayDirectionTransformed, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.00f, 1.00f, 1.00f), 0 });
            std::shared_ptr<Ksm::Mesh> sphere = Ksm::PrimitiveFactory::CreateSphere(0.05f, 36, 18);
            std::vector<Ksm::Mesh> meshes({ *sphere });
            std::shared_ptr<Ksm::Texture> texture = AssetManager::LoadTexture("Assets/Textures/grass.png");
            Entity e(transform, meshes, texture, inGameState, false);
            inGameState->AddEntity(e);

            transform = Ksm::Transform({ rayOriginTransformed, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.00f, 2.00f, 2.00f), 0 });
            Entity e2(transform, meshes, texture, inGameState, false);
            inGameState->AddEntity(e2);

            KLOG_WARN(fmt::format("[{}, {}, {}], [{}, {}, {}]",
                rayOriginTransformed.x,
                rayOriginTransformed.y,
                rayOriginTransformed.z,
                rayDirectionTransformed.x,
                rayDirectionTransformed.y,
                rayDirectionTransformed.z
            ));
            */
        }

        if (clickedEntity)
        {
            entityMeshIndex /= 3;
            KLOG_INFO(fmt::format("E: {}, I: {}, D: {}, P: [{}, {}]",
                entityIndex,
                entityMeshIndex,
                entityDistance,
                entityPos.x,
                entityPos.y
            ));
            MeshClickInfo meshClickInfo(entityIndex, entityMeshIndex, entityDistance, entityPos.x, entityPos.y);
            if (meshClicks.contains(entityMeshIndex))
                meshClicks.erase(entityMeshIndex);
            else
                meshClicks[entityMeshIndex] = meshClickInfo;
        }
    } // if right button
}

void Sphectory::OnMouseRelease(const Ksm::MouseReleaseEvent& ev)
{
    if (ev.GetButton() == GLFW_MOUSE_BUTTON_LEFT)
    {
        this->isDragging = false;
        this->MouseDragDistance = 0.0f;
        glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
