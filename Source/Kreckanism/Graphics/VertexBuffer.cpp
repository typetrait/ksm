#include "Kreckanism/Graphics/VertexBuffer.h"

#include "glad/glad.h"

namespace Ksm
{
    VertexBuffer::VertexBuffer(float* vertices, size_t size) : Buffer(), size(size)
    {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
