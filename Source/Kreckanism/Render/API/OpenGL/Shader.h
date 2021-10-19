#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Ksm
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();
        void Bind() const;
        void Unbind() const;
        void SetUniform(const std::string& name, const glm::vec2& vector) const;
        void SetUniform(const std::string& name, const glm::vec3& vector) const;
        void SetUniform(const std::string& name, const glm::vec4& vector) const;
        void SetUniform(const std::string& name, const glm::mat3& matrix) const;
        void SetUniform(const std::string& name, const glm::mat4& matrix) const;
    private:
        unsigned int id;
    };
}
