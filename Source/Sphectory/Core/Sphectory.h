#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <Kreckanism/Kreckanism.h>

#include <Sphectory/Core/Material.h>
#include <Sphectory/State/InGameState.h>

class Sphectory : public Ksm::Application
{
public:
    void Startup() override;
    void Run() override;
    void Exit() override;

private:
    void OnUpdate(double deltaTime) override;
    void OnWindowResize(const Ksm::WindowResizeEvent& ev) override;
    void OnMouseMove(const Ksm::MouseMoveEvent& ev) override;
    void OnMousePress(const Ksm::MousePressEvent& ev) override;
    void OnMouseRelease(const Ksm::MouseReleaseEvent& ev) override;

    Ksm::Window* window;

    std::shared_ptr<InGameState> inGameState;
    //std::shared_ptr<MainMenuState> mainMenuState;
    //std::shared_ptr<GameOverState> gameOverState;

    glm::vec3 CalcRayDirection(glm::vec2 mousePosition);
    bool IntersectRayMesh(
        glm::vec3 rayOrigin,
        glm::vec3 rayDir,
        Ksm::Mesh mesh,
        unsigned int& intersectMeshIndex,
        glm::vec2& intersectPos,
        float& intersectDistance
    );

    std::unique_ptr<Ksm::PerspectiveCamera> camera;
    bool isDragging = false;
    float MouseDragDistance = 0.0f;
    glm::vec2 MouseDragDelta;
    glm::vec2 MouseDragPrevious;

    struct MeshClickInfo
    {
        unsigned int entityIndex;
        unsigned int entityMeshIndex;
        float entityDistance;
        float entityPosX;
        float entityPosY;
    };

    std::map<unsigned int, MeshClickInfo> meshClicks;

    glm::vec3 lightPos;
    glm::vec3 lightPos2;

    std::map<std::string, std::shared_ptr<Ksm::Shader>> shaders;
    std::map<std::string, glm::mat4> models;
    std::map<std::string, Material> materials;

    bool wireframe = false;
};
