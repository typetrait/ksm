#pragma once

#include "Kreckanism/Core/Kreckanism.h"

class Demo : public Ksm::Application
{
public:
    void Startup() override;
    void Run() override;
    void Exit() override;

    void OnEvent(Ksm::Event& e);
private:
    Ksm::Window* window;
};
