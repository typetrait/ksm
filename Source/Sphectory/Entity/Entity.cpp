#include <Sphectory/Entity/Entity.h>

#include <fmt/format.h>
#include <glm/ext/matrix_transform.hpp>

#include <Kreckanism/Kreckanism.h>

Entity::Entity(Ksm::Transform transform,
    std::vector<Ksm::Mesh> meshes,
    std::shared_ptr<Ksm::Texture> texture,
    std::shared_ptr<InGameState> state,
    bool selectable)
    : transform(transform), meshes(meshes), texture(texture), state(state), selectable(selectable)
{
    model = glm::translate(glm::mat4(1.0f), transform.Position);
    model = glm::rotate(model, transform.RotationAngle, transform.Rotation);
    model = glm::scale(model, transform.Scale);
}

std::vector<Ksm::Mesh> Entity::GetMeshes()
{
    return meshes;
}

Ksm::Transform Entity::GetTransform()
{
    return transform;
}

glm::mat4 Entity::GetModel()
{
    return model;
}

void Entity::BindTexture()
{
    texture->Bind();
}

void Entity::Translate(glm::vec3 amount)
{
    transform.Position = amount;
    model = glm::translate(model, transform.Position);
    KLOG_WARN(fmt::format("{} {} {}", amount.x, amount.y, amount.z));
    KLOG_WARN(fmt::format("{} {} {}", transform.Position.x, transform.Position.y, transform.Position.z));
    KLOG_WARN(fmt::format("--------", amount.x, amount.y, amount.z));
}

void Entity::Rotate(glm::vec3 axis, float angle)
{
    transform.Rotation = axis;
    transform.RotationAngle = angle;
    model = glm::rotate(model, transform.RotationAngle, transform.Rotation);
}

void Entity::Scale(glm::vec3 amount)
{
    transform.Position = amount;
    model = glm::scale(model, transform.Scale);
}

bool Entity::isSelectable()
{
    return selectable;
}
