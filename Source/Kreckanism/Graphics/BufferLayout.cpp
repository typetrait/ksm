#include "Kreckanism/Graphics/BufferLayout.h"

namespace Ksm
{
    BufferLayout::BufferLayout(std::initializer_list<VertexAttribute> attributes) : attributes(attributes)
    {
        for (auto& attribute : attributes)
        {
        }
    }

    const std::vector<VertexAttribute>& BufferLayout::GetAttributes() const
    {
        return attributes;
    }
}