#include <Kreckanism/Render/Renderer.h>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <Kreckanism/Render/API/OpenGL/VertexArray.h>

namespace Ksm
{
    void Renderer::DrawIndexed(std::shared_ptr<VertexArray>& vertexArray)
    {
        glEnable(GL_DEPTH_TEST);
        vertexArray->Bind();
        vertexArray->GetIndexBuffer()->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
