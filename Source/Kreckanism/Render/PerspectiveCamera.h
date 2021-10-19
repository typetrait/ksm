#pragma once

#include <glm/glm.hpp>

namespace Ksm
{
    class PerspectiveCamera
    {
    public:
        PerspectiveCamera();
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewMatrix() const;
        const glm::vec3& GetPosition() const;
        void SetPosition(const glm::vec3& position);
    private:
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 position;
    };
}
