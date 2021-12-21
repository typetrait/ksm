#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <Kreckanism/Kreckanism.h>

class Demo : public Ksm::Application
{
public:
    void Startup() override;
    void Run() override;
    void Exit() override;

private:
    void OnUpdate(double deltaTime) override;

    Ksm::Window* window;
    std::unique_ptr<Ksm::PerspectiveCamera> camera;
    glm::mat4 model;
};
