#include <Kreckanism/Render/PerspectiveCamera.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Ksm
{
    PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar, const glm::vec3& position)
        : fov(fov), aspect(aspect), zNear(zNear), zFar(zFar), position(position)
    {
        projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

        up = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::normalize(glm::cross(up, position));
        forward = glm::vec3(0.0f, 0.0f, -1.0f);

        view = glm::lookAt(position, position + forward, up);
    }

    const glm::vec3 PerspectiveCamera::GetForward() const
    {
        return forward;
    }

    const glm::vec3 PerspectiveCamera::GetRight() const
    {
        return right;
    }

    const glm::mat4& PerspectiveCamera::GetProjectionMatrix() const
    {
        return projection;
    }

    const glm::mat4& PerspectiveCamera::GetViewMatrix()
    {
        view = glm::lookAt(position, position + forward, up);
        return view;
    }

    const glm::vec3& PerspectiveCamera::GetPosition() const
    {
        return position;
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& position)
    {
        this->position = position;
    }

    void PerspectiveCamera::SetAspectRatio(const float aspect)
    {
        this->aspect = aspect;
        projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
    }

    void PerspectiveCamera::Update(glm::vec2 cursorDelta)
    {
        forward = glm::mat3(glm::rotate(cursorDelta.x * 0.0025f, up)) * forward;
        forward = glm::mat3(glm::rotate(cursorDelta.y * 0.0025f, right)) * forward;
        right = glm::normalize(glm::cross(up, position));
    }
}
