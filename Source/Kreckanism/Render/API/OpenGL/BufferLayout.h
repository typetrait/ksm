#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Kreckanism/Render/API/OpenGL/VertexAttribute.h>

namespace Ksm
{
    class BufferLayout
    {
    public:
        unsigned int GetStride() const;
        const std::vector<VertexAttribute>& GetAttributes() const;

        template<typename T>
        void PushAttribute()
        {
        }

    private:
        std::vector<VertexAttribute> attributes;
    };

    template<> inline
    void BufferLayout::PushAttribute<glm::vec2>()
    {
        attributes.push_back(
        {
            .type = GL_FLOAT,
            .count = 2,
            .size = sizeof(glm::vec2)
        });
    }

    template<> inline
    void BufferLayout::PushAttribute<glm::vec3>()
    {
        attributes.push_back(
        {
            .type = GL_FLOAT,
            .count = 3,
            .size = sizeof(glm::vec3)
        });
    }
}
