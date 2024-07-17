#pragma once

#include <string>
#include "Octree.h"

class CLevel
{
public:

	CLevel(std::string LevelName);
	~CLevel(){};

	//__declspec(dllexport) void AddObjectOnScene(uint64_t Mesh, glm::vec3 location);
	//__declspec(dllexport) void AddObjectOnScene(uint64_t Mesh, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale);

	__declspec(dllexport) std::string GetName();

private:
	
	std::string Name;
	COctree Octree;
	
};