#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


// For any Object that can be placed on level
class CSceneObject
{
public:
	CSceneObject(glm::vec3 location) : Location(location) {};
	CSceneObject(glm::vec3 location, glm::vec3 rotation) : Location(location), Rotation(rotation) {};
	~CSceneObject() {};

	void AddModel(uint64_t Model);

	glm::vec3 GetLocation();
	glm::vec3 GetRotation();

	std::vector<uint64_t> GetObjectsModels();

	void Tick() {};

protected:
	glm::vec3 Location;
	// Front vector
	glm::vec3 Rotation;
	glm::vec3 Scale;

	std::vector<uint64_t> Models{};
	std::vector<CSceneObject> ChildObjects{};
};
