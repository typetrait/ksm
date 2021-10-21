#pragma once

#include <glm/glm.hpp>

#include <Kreckanism/Render/API/OpenGL/VertexArray.h>

namespace Ksm
{
    class Renderer
    {
    public:
        static void DrawIndexed(std::shared_ptr<VertexArray>& vertexArray);
        static void Clear(glm::vec4 color);
    private:

    };
}
