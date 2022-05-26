#pragma once

#include <vector>
#include <memory>

#include <Kreckanism/Kreckanism.h>

#include <Sphectory/State/InGameState.h>

class InGameState;

class Entity
{
public:
    Entity(Ksm::Transform transform,
        std::vector<Ksm::Mesh> meshes,
        std::shared_ptr<Ksm::Texture> texture,
        std::shared_ptr<InGameState> state,
        bool selectable=true);

    std::vector<Ksm::Mesh> GetMeshes();
    Ksm::Transform GetTransform();
    glm::mat4 GetModel();
    void BindTexture();
    void Translate(glm::vec3 amount);
    void Rotate(glm::vec3 axis, float angle);
    void Scale(glm::vec3 amount);
    bool isSelectable();
private:
    Ksm::Transform transform;
    std::vector<Ksm::Mesh> meshes;
    std::shared_ptr<Ksm::Texture> texture;
    std::shared_ptr<InGameState> state;

    glm::mat4 model;
    bool selectable;
};
