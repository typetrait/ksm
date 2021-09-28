#pragma once

namespace Ksm
{
    class Application
    {
        virtual void Startup() = 0;
        virtual void Run() = 0;
        virtual void Exit() = 0;
    };
}
