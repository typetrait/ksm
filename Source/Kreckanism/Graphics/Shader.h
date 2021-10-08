#pragma once

#include <string>

namespace Ksm
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();
        void Use() const;
    private:
        unsigned int id;
    };
}
