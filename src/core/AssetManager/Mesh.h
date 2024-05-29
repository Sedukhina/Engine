#pragma once

#include "Asset.h"
#include "../Box.h"


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
	CMesh(std::filesystem::path Path, std::string assetName, std::vector<Vertex>& Vertices, std::vector<unsigned int>& Indices);
	~CMesh() {};

	const int GetVerticesSize() { return Vertices.size() * sizeof(Vertex); };
	const Vertex* GetVertices() { return &Vertices[0]; };
	const int GetIndicesSize() { return Indices.size() * sizeof(unsigned int); };
	const unsigned int* GetIndices() { return &Indices[0]; };

private:
	const std::vector<Vertex> Vertices;
	const std::vector<unsigned int> Indices;

	//CBox BoundingBox;
};
