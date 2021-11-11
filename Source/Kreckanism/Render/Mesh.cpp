#include <Kreckanism/Render/Mesh.h>

#include <vector>

#include <glm/glm.hpp>

#include <Kreckanism/Render/API/OpenGL/VertexArray.h>
#include <Kreckanism/Render/API/OpenGL/VertexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>
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

    std::shared_ptr<Mesh> Mesh::CreateTriangle(float size)
    {
        std::vector<Vertex> vertices =
        {
            {{ -size / 2.0f, -size / 2.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }},
            {{ 0.0f, size / 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f,  -size / 2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }}
        };

        std::vector<unsigned int> indices =
        {
            0, 1, 2
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> Mesh::CreateQuad(float width, float height)
    {
        std::vector<Vertex> vertices =
        {
            {{ -width / 2.0f, -height / 2.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }},
            {{ width / 2.0f, -height / 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }},
            {{ width / 2.0f,  height / 2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
            {{ -width /2.0f, height / 2.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }}
        };

        std::vector<unsigned int> indices =
        {
            0, 1, 2, 2, 3, 0
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> Mesh::CreateCube(float size)
    {
        std::vector<Vertex> vertices =
        {
            {{ -size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ -size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, size / 2.0f, -size / 2.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ -size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }}
        };

        std::vector<unsigned int> indices =
        {
            0, 1, 2, 2, 3, 0,
            3, 2, 6, 6, 7, 3,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            0, 1, 5, 5, 4, 0,
            1, 5, 6, 6, 2, 1
        };

        return std::make_shared<Mesh>(vertices, indices);
    }
}
