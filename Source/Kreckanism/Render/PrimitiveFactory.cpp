#include <Kreckanism/Render/PrimitiveFactory.h>

#include <cmath>

#include <Kreckanism/Render/Mesh.h>
#include <Kreckanism/Render/Vertex.h>

namespace Ksm
{
    std::shared_ptr<Mesh> PrimitiveFactory::CreateTriangle(float size)
    {
        std::vector<Vertex> vertices =
        {
            {{ -size / 2.0f, -size / 2.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }},
            {{ 0.0f, size / 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f,  0.0f }},
            {{ size / 2.0f,  -size / 2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }}
        };

        std::vector<unsigned int> indices =
        {
            0, 1, 2
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateQuad(float width, float height)
    {
        std::vector<Vertex> vertices =
        {
            {{ -width / 2.0f, -height / 2.0f, 0.0f }, { 0.8f, 0.74f, 0.45f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ width / 2.0f, -height / 2.0f, 0.0f }, { 0.8f, 0.74f, 0.45f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }},
            {{ width / 2.0f,  height / 2.0f, 0.0f }, { 0.8f, 0.74f, 0.45f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
            {{ -width / 2.0f, height / 2.0f, 0.0f }, { 0.8f, 0.74f, 0.45f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }}
        };

        std::vector<unsigned int> indices =
        {
            0, 1, 2, 2, 3, 0
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateCube(float size)
    {
        std::vector<Vertex> vertices =
        {
            {{ -size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ -size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { -1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
            {{ -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f }},
            {{ size / 2.0f, size / 2.0f, -size / 2.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f }},
            {{ -size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f }}
        };

        std::vector<unsigned int> indices =
        {
            0, 1, 2, 2, 3, 0,
            3, 2, 6, 6, 7, 3,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            0, 1, 5, 5, 4, 0,
            1, 5, 6, 6, 2, 1
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateSphere(float radius, int sectorCount, int stackCount)
    {
        const float PI = acos(-1);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        float sectorStep = 2 * PI / sectorCount;
        float stackStep = PI / stackCount;
        float sectorAngle, stackAngle;

        for (int i=0; i <= stackCount; ++i)
        {
            stackAngle = PI / 2 - i * stackStep;  // from pi/2 to -pi/2
            float xy = radius * cosf(stackAngle); // r * cos(u)
            float z = radius * sinf(stackAngle);  // r * sin(u)
            for (int j=0; j <= sectorCount; ++j)
            {
                sectorAngle = j * sectorStep;     // from 0 to 2pi
                float x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
                float y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)

                float nx = x / radius;
                float ny = y / radius;
                float nz = z / radius;

                float s = (float) j / sectorCount;
                float t = (float) i / stackCount;

                vertices.push_back({{x, y, z}, { 0.0f, 1.0f, 0.0f }, { nx, ny, nz }, { s, t }});
            }
        }

        for (int i=0; i < stackCount; ++i)
        {
            unsigned int k1 = i * (sectorCount + 1);
            unsigned int k2 = k1 + sectorCount + 1;

            for (int j=0; j < sectorCount; ++j, ++k1, ++k2)
            {
                if (i != 0)
                {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1+1);
                }
                if (i != stackCount - 1)
                {
                    indices.push_back(k1+1);
                    indices.push_back(k2);
                    indices.push_back(k2+1);
                }
            }
        }

        return std::make_shared<Mesh>(vertices, indices);
    }
}
