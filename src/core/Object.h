#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "GlobalConstants.h"
#include "ObjectComponent.h"

// For any Object that can be placed on level
class CSceneObject
{
public:
	CSceneObject(glm::vec3 location, glm::vec3 rotation) : Location(location), Rotation(rotation) {};
	~CSceneObject() {};

	glm::vec3 GetLocation();
	glm::vec3 GetRotation();

protected:
	glm::vec3 Location;
	// Front vector
	glm::vec3 Rotation;

	IObjectComponent* ObjectTreeRoot;
};
