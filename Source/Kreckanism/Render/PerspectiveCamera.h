#pragma once

#include <glm/glm.hpp>

namespace Ksm
{
    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(float fov, float aspect, float zNear, float zFar, const glm::vec3& position);
        const glm::vec3 GetForward() const;
        const glm::vec3 GetRight() const;
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewMatrix();
        const glm::vec3& GetPosition() const;
        void SetPosition(const glm::vec3& position);
        void SetAspectRatio(const float aspect);

    private:
        float fov;
        float aspect;
        float zNear;
        float zFar;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 forward;
        glm::vec3 position;
        glm::mat4 projection;
        glm::mat4 view;
    };
}
