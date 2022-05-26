#pragma once

#include <string>

#include <Kreckanism/Kreckanism.h>

class GeometryShader : public Ksm::Shader
{
public:
    GeometryShader(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath,
        const std::string& geometryShaderPath
    );
private:
};
