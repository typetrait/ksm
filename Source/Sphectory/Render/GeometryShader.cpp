#include <Sphectory/Render/GeometryShader.h>

#include <filesystem>
#include <fstream>
#include <string>

GeometryShader::GeometryShader(
    const std::string& vertexShaderPath,
    const std::string& fragmentShaderPath,
    const std::string& geometryShaderPath)
{
    // Geometry
    auto geometryPath = std::filesystem::path(geometryShaderPath);
    auto geometryFileSize = std::filesystem::file_size(geometryPath);

    std::string geometryShaderSource(geometryFileSize, '\0');
    std::ifstream geometryFile(geometryPath, std::ios::in | std::ios::binary);
    geometryFile.read(&geometryShaderSource[0], geometryFileSize);
    geometryFile.close();
    const char* geometryShaderSource2 = geometryShaderSource.c_str();

    const unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

    glShaderSource(geometryShader, 1, &geometryShaderSource2, nullptr);
    glCompileShader(geometryShader);

    // Vertex and Fragment
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

    // Program
    id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glAttachShader(id, geometryShader);
    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}
