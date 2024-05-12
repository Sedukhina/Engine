#pragma once

#include "Asset.h"

class CMesh : public Asset
{
public:
	CMesh(std::filesystem::path Path, std::string assetName, std::vector<float> &Vertices, std::vector<unsigned int> &Indices);
	~CMesh() {};

	const int GetVerticesSize() { return Vertices.size() * sizeof(float); };
	const float* GetVertices() { return &Vertices[0]; };
	const int GetIndicesSize() { return Indices.size() * sizeof(unsigned int); };
	const unsigned int* GetIndices() { return &Indices[0] ; };

private:
	// Vertices stored dense
	// 3 floats for position + 3 for normal + 2 Texture Coordinates

	const std::vector<float> Vertices;
	const std::vector<unsigned int> Indices;

	/*
	const float* Vertices;
	const int AmountOfVertices;
	const unsigned int* Indices;
	const int AmountOfIndices;*/
};
