#include "Level.h"

void CLevel::AddModelOnScene(uint64_t Model, glm::vec3 location)
{
	CSceneObject Object = CSceneObject(location);
	Object.AddModel(Model);
	ObjectsOnScene.emplace_back(Object);
}

std::vector<CSceneObject> CLevel::GetSceneObjects()
{
	return ObjectsOnScene;
}
