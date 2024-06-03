#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


// For any Object that can be placed on level
class CSceneObject
{
public:
	CSceneObject(glm::vec3 location) : Location(location) { UpdateModelMatrix(); };
	CSceneObject(glm::vec3 location, glm::vec3 rotation) : Location(location), RotationAngle(rotation) { UpdateModelMatrix(); };
	~CSceneObject() {};

	__declspec(dllexport) void AddModel(uint64_t Model);

	__declspec(dllexport) void SetScale(float scale);
	__declspec(dllexport) void SetScale(float x, float y, float z);
	__declspec(dllexport) void SetScale(glm::vec3 Scale);
	__declspec(dllexport) void SetRotationX(float x);
	__declspec(dllexport) void SetRotationY(float y);
	__declspec(dllexport) void SetRotationZ(float z);
	__declspec(dllexport) void SetRotation(float x, float y, float z);
	__declspec(dllexport) void SetRotation(glm::vec3 Rotation);
	__declspec(dllexport) void SetLocation(float x, float y, float z);
	__declspec(dllexport) void SetLocation(glm::vec3 Location);

	__declspec(dllexport) glm::vec3 GetScale() { return Scale; };
	__declspec(dllexport) float GetRotationX() { return RotationAngle.x; };
	__declspec(dllexport) float GetRotationY() { return RotationAngle.y; };
	__declspec(dllexport) float GetRotationZ() { return RotationAngle.z; };
	__declspec(dllexport) glm::vec3 GetRotation() { return RotationAngle; }
	__declspec(dllexport) glm::vec3 GetLocation() { return Location; };

	__declspec(dllexport) std::vector<uint64_t> GetObjectsModels();
	__declspec(dllexport) glm::mat4 GetModelMatrix() { return ModelMatrix; };

	void Tick() {};

protected:
	void UpdateModelMatrix();

	glm::mat4 ModelMatrix = glm::mat4(1);

	glm::vec3 Location;
	// Front vector
	glm::vec3 RotationAngle = glm::vec3(0);
	glm::vec3 Scale = glm::vec3(1);

	std::vector<uint64_t> Models{};
	std::vector<CSceneObject> ChildObjects{};
};
