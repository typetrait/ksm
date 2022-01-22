#include <Kreckanism/Render/Renderer.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Kreckanism/Render/API/OpenGL/VertexArray.h>

namespace Ksm
{
    void Renderer::Draw(std::shared_ptr<VertexArray>& vertexArray, int count)
    {
        glEnable(GL_DEPTH_TEST);
        vertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void Renderer::DrawIndexed(std::shared_ptr<VertexArray>& vertexArray)
    {
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
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
