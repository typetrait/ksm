#pragma once

#include <memory>

#include "Kreckanism/Graphics/VertexBuffer.h"
#include "Kreckanism/Graphics/IndexBuffer.h"

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
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    private:
        unsigned int id;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}
