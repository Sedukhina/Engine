#pragma once

#include <vector>
#include "Object.h"

class CLevel
{
public:

	CLevel(){};
	~CLevel(){};

	void AddModelOnScene(uint64_t Model, glm::vec3 location);

	std::vector<CSceneObject> GetSceneObjects();

private:
	// TO DO: Make BVH instead
	std::vector<CSceneObject> ObjectsOnScene;
};