#include "Kreckanism/Graphics/Shader.h"

#include <filesystem>
#include <fstream>

#include "glad/glad.h"

namespace Ksm
{
    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        auto vertexPath = std::filesystem::path(vertexShaderPath);
        auto fragmentPath = std::filesystem::path(fragmentShaderPath);

        auto vertexFileSize = std::filesystem::file_size(vertexPath);
        auto fragmentFileSize = std::filesystem::file_size(fragmentPath);

        std::string vertexShaderSource(vertexFileSize, '\0');
        std::string fragmentShaderSource(fragmentFileSize, '\0');

        std::ifstream vertexFile(vertexPath, std::ios::in | std::ios::binary);
        vertexFile.read(&vertexShaderSource[0], vertexFileSize);
        vertexFile.close();

        std::ifstream fragmentFile(fragmentPath, std::ios::in | std::ios::binary);
        fragmentFile.read(&fragmentShaderSource[0], fragmentFileSize);
        fragmentFile.close();

        const char* vertexShaderSource2 = vertexShaderSource.c_str();
        const char* fragmentShaderSource2 = fragmentShaderSource.c_str();

        const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexShaderSource2, nullptr);
        glCompileShader(vertexShader);

        const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fragmentShaderSource2, nullptr);
        glCompileShader(fragmentShader);

        id = glCreateProgram();

        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(id);
    }

    void Shader::Use() const
    {
        glUseProgram(id);
    }
}
