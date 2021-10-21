#pragma once

#include <memory>

#include <Kreckanism/Render/API/OpenGL/VertexBuffer.h>
#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>

namespace Ksm
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        void Bind() const;
        void Unbind() const;
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    private:
        unsigned int id;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}
