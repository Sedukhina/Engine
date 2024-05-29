#pragma once

#include "Asset.h"
#include "glm/glm.hpp"

class CModel : public Asset
{
public:
	CModel(std::filesystem::path Path, std::string ModelName, uint64_t mesh);
	~CModel() {};

	bool HasMaterial() { return MaterialID !=  0;  };

	void SetScale(float scale);
	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 Scale);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 Rotation);
	void SetLocation(float x, float y, float z);
	void SetLocation(glm::vec3 Location);

	glm::vec3 GetScale() { return Scale;  };
	float GetRotationX() { return RotationAngle.x; };
	float GetRotationY() { return RotationAngle.y; };
	float GetRotationZ() { return RotationAngle.z; };
	glm::vec3 GetRotation() { return RotationAngle;  }
	glm::vec3 GetLocation() { return Location; };

	uint64_t GetMesh() { return MeshID; };
	uint64_t GetMaterial() { return MaterialID; };
	glm::mat4 GetModelMatrix();

	void SetMaterial(uint64_t Material);


private:
	glm::mat4 ModelMatrix = glm::mat4(1);

	glm::vec3 Scale = glm::vec3(1);
	glm::vec3 RotationAngle = glm::vec3(0);
	glm::vec3 Location = glm::vec3(0);

	uint64_t MeshID;
	uint64_t MaterialID = 0;

	void UpdateModelMatrix();
};

