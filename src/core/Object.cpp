#include "Object.h"
#include <vector>

#include "AssetManager/ModelMatrix.h"

void CSceneObject::SetScale(float scale)
{
	SetScale(glm::vec3(scale));
}

void CSceneObject::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}

void CSceneObject::SetScale(glm::vec3 scale)
{
	Scale = scale;
	UpdateModelMatrix();
}

void CSceneObject::SetRotationX(float x)
{
	RotationAngle.x = x;
	UpdateModelMatrix();
}

void CSceneObject::SetRotationY(float y)
{
	RotationAngle.y = y;
	UpdateModelMatrix();
}

void CSceneObject::SetRotationZ(float z)
{
	RotationAngle.z = z;
	UpdateModelMatrix();
}

void CSceneObject::SetRotation(float x, float y, float z)
{
	SetRotation(glm::vec3(x, y, z));
}

void CSceneObject::SetRotation(glm::vec3 rotation)
{
	RotationAngle = rotation;
	while (RotationAngle.x > 360)
	{
		RotationAngle.x -= 360;
	}
	while (RotationAngle.x < 0)
	{
		RotationAngle.x += 360;
	}
	while (RotationAngle.y > 360)
	{
		RotationAngle.y -= 360;
	}
	while (RotationAngle.y < 0)
	{
		RotationAngle.y += 360;
	}
	while (RotationAngle.z > 360)
	{
		RotationAngle.z -= 360;
	}
	while (RotationAngle.z < 0)
	{
		RotationAngle.z += 360;
	}
	UpdateModelMatrix();
}

void CSceneObject::SetLocation(float x, float y, float z)
{
	SetLocation(glm::vec3(x, y, z));
}

void CSceneObject::SetLocation(glm::vec3 location)
{
	Location = location;
	UpdateModelMatrix();
}

std::vector<uint64_t> CSceneObject::GetObjectsModels()
{
    return Models;
}

void CSceneObject::AddModel(uint64_t Model)
{
    Models.emplace_back(Model);
}

void CSceneObject::UpdateModelMatrix()
{
    ModelMatrix = CreateModelMatrix(Scale, Location, RotationAngle);
}