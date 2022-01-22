#pragma once

#include <memory>

#include <Kreckanism/Render/Mesh.h>

namespace Ksm
{
    class PrimitiveFactory
    {
    public:
        static std::shared_ptr<Mesh> CreateTriangle(float size);
        static std::shared_ptr<Mesh> CreateQuad(float width, float height);
        static std::shared_ptr<Mesh> CreateCube(float size);
        static std::shared_ptr<Mesh> CreateSphere(float radius, int sectorCount, int stackCount);

    private:
    };
}
