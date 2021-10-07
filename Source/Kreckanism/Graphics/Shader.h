#pragma once

#include <string>

namespace Ksm
{
    class Shader
    {
    public:
        Shader(const std::string& filepath);
        ~Shader();
        void Use() const;
    private:
        unsigned int id;
    };
}