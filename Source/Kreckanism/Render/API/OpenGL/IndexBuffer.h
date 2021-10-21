#pragma once

#include <cstdlib>

#include <Kreckanism/Render/API/OpenGL/Buffer.h>

namespace Ksm
{
    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(unsigned int* indices, size_t count);
        void Bind() const override;
        void Unbind() const override;
        size_t GetCount() const;
    private:
        size_t count;
    };
}
