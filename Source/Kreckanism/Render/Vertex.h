#pragma once

#include <glm/glm.hpp>

namespace Ksm
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec3 Normal;
        glm::vec2 Texture;
    };
}
