#include "Kreckanism/Core/DeltaTime.h"

#include <algorithm>
#include <chrono>
#include <thread>

#define BILLION 1000000000.0

namespace Ksm
{
    DeltaTime::DeltaTime()
    {
        start = std::chrono::steady_clock::now();
    }

    void DeltaTime::Update()
    {
        end = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / BILLION;
        start = end;
    }

    double DeltaTime::Get()
    {
        return delta;
    }
}
