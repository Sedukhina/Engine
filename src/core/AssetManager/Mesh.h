#pragma once

#include "Asset.h"
#include "../AABB.h"


struct Vertex
{
	float PositionX;
	float PositionY;
	float PositionZ;

	float NormalX;
	float NormalY;
	float NormalZ;

	float TextureCoordinateX;
	float TextureCoordinateY;
};

class CMesh : public Asset
{
public:
	// Constructor for mesh import
	CMesh(std::filesystem::path sourcePath, std::filesystem::path Path, std::string assetName, std::vector<Vertex>& Vertices, std::vector<unsigned int>& Indices, CAABB Box);
	~CMesh() {};

	void SetMaterial(uint64_t material, int MaterialIndex);

	std::filesystem::path GetSourcePath();

	__declspec(dllexport) const int GetVerticesSize() { return Vertices.size() * sizeof(Vertex); };
	__declspec(dllexport) const Vertex* GetVertices() { return &Vertices[0]; };
	__declspec(dllexport) const int GetIndicesSize() { return Indices.size() * sizeof(unsigned int); };
	__declspec(dllexport) const unsigned int* GetIndices() { return &Indices[0]; };

private:
	const std::vector<Vertex> Vertices;
	const std::vector<unsigned int> Indices;

	// AABB for Scene Octree
	CAABB BoundingBox;

	std::filesystem::path SourcePath;

	// Mesh can have up to 3 materials
	int MaterialsAmount = 1;
	uint64_t Material_0 = 0;
	uint64_t Material_1 = 0;
	uint64_t Material_2 = 0;

	void AddMaterialSlot();
	void DeleteMaterialSlot();
};
