#include <Sphectory/State/InGameState.h>

InGameState::InGameState() { }

void InGameState::Update() { }

void InGameState::Render() { }

void InGameState::AddEntity(Entity e)
{
    entities.push_back(e);
}

std::vector<Entity> InGameState::GetEntities()
{
    return entities;
}

void InGameState::TranslateEntity(unsigned int index, glm::vec3 amount)
{
    if (index > entities.size())
        return;
    entities[index].Translate(amount);
}

void InGameState::RotateEntity(unsigned int index, glm::vec3 axis, float angle)
{
    if (index > entities.size())
        return;
    entities[index].Rotate(axis, angle);
}

void InGameState::ScaleEntity(unsigned int index, glm::vec3 amount)
{
    if (index > entities.size())
        return;
    entities[index].Scale(amount);
}
