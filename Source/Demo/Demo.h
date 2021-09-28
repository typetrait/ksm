#pragma once

#include "Kreckanism/Core/Kreckanism.h"

class Demo : public Ksm::Application
{
public:
    void Startup();
    void Run();
    void Exit();
private:
    Ksm::Window* window;
};
