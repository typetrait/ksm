#pragma once

#include <cstdlib>

#include "Kreckanism/Graphics/Buffer.h"

namespace Ksm
{
    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(unsigned int* indices, size_t count);
        void Bind() const override;
        void Unbind() const override;
    private:
        size_t count;
    };
}
