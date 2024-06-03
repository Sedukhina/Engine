#include "ModelMatrix.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

glm::mat4 CreateModelMatrix(glm::vec3 Scale, glm::vec3 Location, glm::vec3 RotationAngle)
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
	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
	return ModelMatrix;
}