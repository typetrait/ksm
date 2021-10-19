#include <Kreckanism/Render/PerspectiveCamera.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Ksm
{
    PerspectiveCamera::PerspectiveCamera() : projection(glm::mat4()), view(glm::mat4()), position(glm::vec3())
    {
        projection = glm::perspective(75.0f, 16.0f / 9.0f, 10.0f, 100.0f);
    }

    const glm::mat4& PerspectiveCamera::GetProjectionMatrix() const
    {
        return projection;
    }

    const glm::mat4& PerspectiveCamera::GetViewMatrix() const
    {
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
}
