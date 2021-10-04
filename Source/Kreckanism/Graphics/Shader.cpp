#include "Kreckanism/Graphics/Shader.h"

#include "glad/glad.h"

namespace Ksm
{
	Shader::Shader(const std::string& filepath)
	{
        const char* vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        const char* fragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";

        const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
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