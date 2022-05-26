#pragma once

#include <vector>

#include <Sphectory/State/State.h>
#include <Sphectory/Entity/Entity.h>

class Entity;

class InGameState : public State
{
public:
    InGameState();
    void Update();
    void Render();
    void AddEntity(Entity e);
    std::vector<Entity> GetEntities();
    void TranslateEntity(unsigned int index, glm::vec3 amount);
    void RotateEntity(unsigned int index, glm::vec3 axis, float angle);
    void ScaleEntity(unsigned int index, glm::vec3 amount);
private:
    std::vector<Entity> entities;
};
