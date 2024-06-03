#pragma once

#include <vector>
#include "Object.h"

class CLevel
{
public:

	CLevel(){};
	~CLevel(){};

	__declspec(dllexport) void AddModelOnScene(uint64_t Model, glm::vec3 location);

	__declspec(dllexport) std::vector<CSceneObject> GetSceneObjects();

private:
	// TO DO: Make BVH instead
	std::vector<CSceneObject> ObjectsOnScene;
};