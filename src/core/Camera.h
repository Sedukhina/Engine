#pragma once

#include "Object.h"

class SCamera : public CSceneObject
{
public:
	SCamera(glm::vec3 location, glm::vec3 rotation);
	~SCamera() {};

	__declspec(dllexport) glm::mat4 GetCameraPerspectiveMatrix(float ScreenRatio);

private:
	bool Orthographic = 0;
	float FOV = 90;
	float MinDistance = 5;
	float MaxDistance = 1000;

	glm::mat4 CameraPerspectiveMatrix;

	void SCamera::UpdatePerspectiveMatrix();

	// Ratio: width/height
	float CachedScreenRatio = 1;
};
