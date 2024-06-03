#pragma once

#include "Asset.h"

class CModel : public Asset
{
public:
	CModel(std::filesystem::path Path, std::string ModelName, uint64_t mesh);
	~CModel() {};

	__declspec(dllexport) bool HasMaterial() { return MaterialID != 0; };

	__declspec(dllexport) void SetMaterial(uint64_t Material);

	__declspec(dllexport) uint64_t GetMesh() { return MeshID; };
	__declspec(dllexport) uint64_t GetMaterial() { return MaterialID; };

private:
	uint64_t MeshID;
	uint64_t MaterialID = 0;

};