#include "Kreckanism/Graphics/VertexArray.h"

#include "glad/glad.h"

namespace Ksm
{
    VertexArray::VertexArray() : indexBuffer()
    {
        glGenVertexArrays(1, &id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(id);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        this->indexBuffer = indexBuffer;
    }
}
