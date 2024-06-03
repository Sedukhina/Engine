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
	CMesh(std::filesystem::path Path, std::string assetName, std::vector<Vertex>& Vertices, std::vector<unsigned int>& Indices, CAABB Box);
	~CMesh() {};

	__declspec(dllexport) const int GetVerticesSize() { return Vertices.size() * sizeof(Vertex); };
	__declspec(dllexport) const Vertex* GetVertices() { return &Vertices[0]; };
	__declspec(dllexport) const int GetIndicesSize() { return Indices.size() * sizeof(unsigned int); };
	__declspec(dllexport) const unsigned int* GetIndices() { return &Indices[0]; };

private:
	const std::vector<Vertex> Vertices;
	const std::vector<unsigned int> Indices;

	CAABB BoundingBox;
};
