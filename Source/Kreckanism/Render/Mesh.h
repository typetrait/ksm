#pragma once

#include <vector>

#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/VertexArray.h>
#include <Kreckanism/Render/API/OpenGL/VertexBuffer.h>
#include <Kreckanism/Render/Vertex.h>

namespace Ksm
{
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> vertices);
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        std::shared_ptr<VertexArray>& GetVertexArray();
        std::shared_ptr<VertexBuffer>& GetVertexBuffer();
        std::shared_ptr<IndexBuffer>& GetIndexBuffer();
        std::vector<Vertex> GetVertices();

    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}
