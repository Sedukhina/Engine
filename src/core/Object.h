#pragma once

#include <glm/glm.hpp>
#include "ObjectComponent.h"

//For any Object that can be placed on level
class CObject
{
public:
	CObject() {};
	~CObject() {};

	glm::vec3 GetLocation();
	glm::vec3 GetRotation();

private:
	glm::vec3 location;
	glm::vec3 rotation;

	IObjectComponent* ObjectTreeRoot;
};
