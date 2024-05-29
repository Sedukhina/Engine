#pragma once

#include "Model.h"
#include "Logger.h"
#include "AssetManager.h"
#include "GetGameGlobals.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

CModel::CModel(std::filesystem::path Path, std::string assetName, uint64_t mesh) 
	: Asset(Path, assetName), MeshID(mesh)
{
	UpdateModelMatrix();
}

void CModel::UpdateModelMatrix()
{
	glm::mat4 ScaleMatrix = glm::mat4(0);
	ScaleMatrix[0][0] = Scale.x;
	ScaleMatrix[1][1] = Scale.y;
	ScaleMatrix[2][2] = Scale.z;
	ScaleMatrix[3][3] = 1;

	glm::mat4 TranslationMatrix = glm::mat4(0);
	TranslationMatrix[0][0] = 1;
	TranslationMatrix[1][1] = 1;
	TranslationMatrix[2][2] = 1;
	TranslationMatrix[3][3] = 1;
	TranslationMatrix[3][0] = -Location.x;
	TranslationMatrix[3][1] = -Location.y;
	TranslationMatrix[3][2] = -Location.z;

	float AngleX = glm::radians(RotationAngle.x);
	float AngleY = glm::radians(RotationAngle.y);
	float AngleZ = glm::radians(RotationAngle.z);
	float Qx = glm::sin(AngleZ * 0.5f) * glm::cos(AngleY * 0.5f) * glm::cos(AngleX * 0.5f) - glm::cos(AngleZ * 0.5f) * glm::sin(AngleY * 0.5f) * glm::sin(AngleX * 0.5f);
	float Qy = glm::cos(AngleZ * 0.5f) * glm::sin(AngleY * 0.5f) * glm::cos(AngleX * 0.5f) + glm::sin(AngleZ * 0.5f) * glm::cos(AngleY * 0.5f) * glm::sin(AngleX * 0.5f);;
	float Qz = glm::cos(AngleZ * 0.5f) * glm::cos(AngleY * 0.5f) * glm::sin(AngleX * 0.5f) - glm::sin(AngleZ * 0.5f) * glm::sin(AngleY * 0.5f) * glm::cos(AngleX * 0.5f);;
	float Qw = glm::cos(AngleZ * 0.5f) * glm::cos(AngleY * 0.5f) * glm::cos(AngleX * 0.5f) + glm::sin(AngleZ * 0.5f) * glm::sin(AngleY * 0.5f) * glm::sin(AngleX * 0.5f);;

	glm::quat Quat = glm::quat(Qw, Qx, Qy, Qz);
	Quat = glm::normalize(Quat);
	Qw = Quat.w;
	Qx = Quat.x;
	Qy = Quat.y;
	Qz = Quat.z;

	float Qw_sqr = Qw * Qw;
	float Qx_sqr = Qx * Qx;
	float Qy_sqr = Qy * Qy;
	float Qz_sqr = Qz * Qz;

	glm::mat4 RotationMatrix = glm::mat4(0);
	RotationMatrix[3][3] = 1;

	RotationMatrix[0][0] = Qw_sqr + Qx_sqr - Qy_sqr - Qz_sqr;
	RotationMatrix[0][1] = 2 * (Qx * Qy + Qw * Qz);
	RotationMatrix[0][2] = 2 * (Qx * Qz - Qw * Qy);

	RotationMatrix[1][0] = 2 * (Qx * Qy - Qw * Qz);
	RotationMatrix[1][1] = Qw_sqr - Qx_sqr + Qy_sqr - Qz_sqr;
	RotationMatrix[1][2] = 2 * (Qz * Qy + Qw * Qx);

	RotationMatrix[2][0] = 2 * (Qx * Qz + Qw * Qy);
	RotationMatrix[2][1] = 2 * (Qy * Qz - Qw * Qx);
	RotationMatrix[2][2] = Qw_sqr - Qx_sqr - Qy_sqr + Qz_sqr;;

	//TranslationMatrix* RotationMatrix* ScaleMatrix* OriginalVector;
	ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
}

void CModel::SetScale(float scale)
{
	SetScale(glm::vec3(scale));
}

void CModel::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}

void CModel::SetScale(glm::vec3 scale)
{
	Scale = scale;
	UpdateModelMatrix();
}

void CModel::SetRotationX(float x)
{
	RotationAngle.x = x;
	UpdateModelMatrix();
}

void CModel::SetRotationY(float y)
{
	RotationAngle.y = y;
	UpdateModelMatrix();
}

void CModel::SetRotationZ(float z)
{
	RotationAngle.z = z;
	UpdateModelMatrix();
}

void CModel::SetRotation(float x, float y, float z)
{
	SetRotation(glm::vec3(x, y, z));
}

void CModel::SetRotation(glm::vec3 rotation)
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

void CModel::SetLocation(float x, float y, float z)
{
	SetLocation(glm::vec3(x, y, z));
}

void CModel::SetLocation(glm::vec3 location)
{
	Location = location;
	UpdateModelMatrix();
}

glm::mat4 CModel::GetModelMatrix()
{
	return ModelMatrix;
}

void CModel::SetMaterial(uint64_t Material)
{
	if (GetAssetManager().GetMaterial(Material))
	{
		MaterialID = Material;
	}
	else
	{
		LOG_ERROR("CModel::SetMaterial: No material was found with provided ID");
	}
}