#pragma once

#include "Object.h"

class SCamera : public CSceneObject
{
public:
	SCamera(glm::vec3 location, glm::vec3 rotation) : CSceneObject(location, rotation) {};
	~SCamera() {};
	// Ratio: width/height
	glm::mat4 GetCameraPerspectiveMatrix(float ScreenRatio);

private:
	bool Orthographic = 0;
	int FOV = 90;
	int MinDistance = 5;
	int MaxDistance = 100;
};
