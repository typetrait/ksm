#include "Kreckanism/Core/Logger.h"

#include <iostream>
#include <string>

namespace Ksm
{
    void Logger::Info(std::string message)
    {
        std::cout << "[INFO] " << message << std::endl;
    }

    void Logger::Warn(std::string message)
    {
        std::cout << "[WARN] " << message << std::endl;
    }

    void Logger::Fail(std::string message)
    {
        std::cerr << "[FAIL] " << message << std::endl;
    }
}
