#pragma once

#include <string>

#define KLOG_INFO(message) Ksm::Logger::Info(message);
#define KLOG_WARN(message) Ksm::Logger::Warn(message);
#define KLOG_FAIL(message) Ksm::Logger::Fail(message);

namespace Ksm
{
    class Logger
    {
    public:
        static void Info(std::string message);
        static void Warn(std::string message);
        static void Fail(std::string message);
    };
}
