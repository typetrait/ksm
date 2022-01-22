#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <Demo/Core/Material.h>
#include <Kreckanism/Kreckanism.h>

class Demo : public Ksm::Application
{
public:
    void Startup() override;
    void Run() override;
    void Exit() override;

private:
    void OnUpdate(double deltaTime) override;
    void OnWindowResize(const Ksm::WindowResizeEvent& ev) override;

    Ksm::Window* window;

    std::unique_ptr<Ksm::PerspectiveCamera> camera;

    glm::vec3 lightPos;
    glm::vec3 lightPos2;

    std::map<std::string, std::shared_ptr<Ksm::Shader>> shaders;
    std::map<std::string, glm::mat4> models;
    std::map<std::string, Material> materials;
};
