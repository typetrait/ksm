#include <Kreckanism/Render/Mesh.h>

#include <vector>

#include <glm/glm.hpp>

#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/VertexArray.h>
#include <Kreckanism/Render/API/OpenGL/VertexBuffer.h>
#include <Kreckanism/Render/Vertex.h>

namespace Ksm
{
    Mesh::Mesh(std::vector<Vertex> vertices) : vertices(vertices)
    {
        vertexArray = std::make_shared<VertexArray>();
        vertexBuffer = std::make_shared<VertexBuffer>(reinterpret_cast<float*>(&vertices[0]), vertices.size() * sizeof(Vertex));

        BufferLayout layout;
        layout.PushAttribute<glm::vec3>();
        layout.PushAttribute<glm::vec3>();
        layout.PushAttribute<glm::vec3>();
        layout.PushAttribute<glm::vec2>();

        vertexBuffer->SetLayout(layout);

        vertexArray->AddVertexBuffer(vertexBuffer);
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices)
    {
        vertexArray = std::make_shared<VertexArray>();
        vertexBuffer = std::make_shared<VertexBuffer>(reinterpret_cast<float*>(&vertices[0]), vertices.size() * sizeof(Vertex));
        indexBuffer = std::make_shared<IndexBuffer>(reinterpret_cast<unsigned int*>(&indices[0]), indices.size());

        BufferLayout layout;
        layout.PushAttribute<glm::vec3>();
        layout.PushAttribute<glm::vec3>();
        layout.PushAttribute<glm::vec3>();
        layout.PushAttribute<glm::vec2>();

        vertexBuffer->SetLayout(layout);

        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
    }

    std::shared_ptr<VertexArray>& Mesh::GetVertexArray()
    {
        return vertexArray;
    }

    std::shared_ptr<VertexBuffer>& Mesh::GetVertexBuffer()
    {
        return vertexBuffer;
    }

    std::shared_ptr<IndexBuffer>& Mesh::GetIndexBuffer()
    {
        return indexBuffer;
    }

    std::vector<Vertex> Mesh::GetVertices()
    {
        return vertices;
    }
}
