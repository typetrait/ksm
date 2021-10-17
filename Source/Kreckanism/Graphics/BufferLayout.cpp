#include "Kreckanism/Graphics/BufferLayout.h"

namespace Ksm
{
    unsigned int BufferLayout::GetStride() const
    {
        unsigned int stride = 0;
        for (auto& attribute : attributes)
        {
            stride += attribute.size;
        }

        return stride;
    }

    const std::vector<VertexAttribute>& BufferLayout::GetAttributes() const
    {
        return attributes;
    }
}
