#pragma once

#include <memory>
#include "Camera.h"

class SPlayer : public CSceneObject
{
public:
	SPlayer(glm::vec3 location, glm::vec3 rotation, SCamera Camera) : CSceneObject(location) { CurrentCamera = std::make_shared<SCamera>(Camera);  };
	~SPlayer() {};

	SCamera* GetCurrentCamera() { return CurrentCamera.get(); };
private:
	std::shared_ptr<SCamera> CurrentCamera;
};
