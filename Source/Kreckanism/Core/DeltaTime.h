#pragma once

#include <chrono>

namespace Ksm
{
    class DeltaTime
    {
    public:
        DeltaTime();
        void Update();
        double Get();

    private:
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> end;
        double delta;
    };
}
