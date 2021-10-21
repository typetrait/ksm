#include <Kreckanism/Render/API/OpenGL/IndexBuffer.h>

#include <glad/glad.h>

namespace Ksm
{
    IndexBuffer::IndexBuffer(unsigned int* indices, size_t count) : Buffer(), count(count)
    {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    size_t IndexBuffer::GetCount() const
    {
        return count;
    }
}
