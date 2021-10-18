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

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        Bind();
        vertexBuffer->Bind();

        BufferLayout layout = vertexBuffer->GetLayout();

        unsigned int stride = layout.GetStride();

        unsigned int index = 0;
        unsigned int offset = 0;
        for (const auto& attribute : layout.GetAttributes())
        {
            glVertexAttribPointer(index, attribute.count, attribute.type, GL_FALSE, stride, (void*)offset);
            glEnableVertexAttribArray(index);

            index++;
            offset += attribute.size;
        }
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        Bind();
        indexBuffer->Bind();

        this->indexBuffer = indexBuffer;
    }
}
