#include "Object.h"
#include <vector>

glm::vec3 CSceneObject::GetLocation()
{
    return Location;
}

glm::vec3 CSceneObject::GetRotation()
{
    return Rotation;
}

std::vector<uint64_t> CSceneObject::GetObjectsModels()
{
    return Models;
}

void CSceneObject::AddModel(uint64_t Model)
{
    Models.emplace_back(Model);
}