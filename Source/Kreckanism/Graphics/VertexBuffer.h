#pragma once

#include <cstdlib>

#include "Kreckanism/Graphics/Buffer.h"
#include "Kreckanism/Graphics/BufferLayout.h"

namespace Ksm
{
    class VertexBuffer : public Buffer
    {
    public:
        VertexBuffer(float* vertices, size_t size);
        void Bind() const override;
        void Unbind() const override;
        const BufferLayout& GetLayout() const { return layout; }
        void SetLayout(const BufferLayout& layout) { this->layout = layout; }
    private:
        size_t size;
        BufferLayout layout;
    };
}
