#pragma once

#include "Mesh.h"
#include <map>

class aiNode;
class aiScene;

class CAssetManager {
public:
	CAssetManager();
	~CAssetManager() {};

	// Returns AssetIDs if succesful or empty vector any other case
	std::vector<uint64_t> ImportModel(std::filesystem::path Path);

	CMesh* GetMesh(uint64_t ID);
	//TEMP
	CMesh* GetMesh();

private:
	// Use count of each asset by ID
	std::map<uint64_t, int> UseCount;

	//TEMP //Make a memory or smth then
	std::map<uint64_t, std::unique_ptr<CMesh>> Meshes;

	void ProcessAssimpScene(aiNode* Node, const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* Model);
	bool IsExistingPath(std::filesystem::path* Path);
};