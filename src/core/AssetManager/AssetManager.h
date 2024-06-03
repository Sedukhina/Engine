#pragma once

#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include <map>

class aiNode;
class aiScene;

class CAssetManager {
public:
	CAssetManager() {};
	~CAssetManager() {};

	// First vector with models, second with meshes and third with materials
	__declspec(dllexport) std::vector<std::vector<uint64_t>> ImportModel(std::filesystem::path Path);
	__declspec(dllexport) uint64_t ImportTexture(std::filesystem::path Path);

	// Creates empty material
	__declspec(dllexport) uint64_t CreateMaterial(std::string Name);

	__declspec(dllexport) bool IsExistingMesh(uint64_t ID);
	__declspec(dllexport) bool IsExistingTexture(uint64_t ID);
	__declspec(dllexport) bool IsExistingMaterial(uint64_t ID);
	__declspec(dllexport) bool IsExistingModel(uint64_t ID);

	__declspec(dllexport) CMesh* GetMesh(uint64_t ID);
	__declspec(dllexport) CTexture* GetTexture(uint64_t ID);
	__declspec(dllexport) CMaterial* GetMaterial(uint64_t ID);
	__declspec(dllexport) CModel* GetModel(uint64_t ID);


private:
	// Use count of each asset by ID
	// Can be zero if asset not loaded
	std::map<uint64_t, int> UseCount;

	// TO DO: More effective memory allocation
	std::map<uint64_t, std::unique_ptr<CMesh>> Meshes;
	std::map<uint64_t, std::unique_ptr<CTexture>> Textures;
	std::map<uint64_t, std::unique_ptr<CMaterial>> Materials;
	std::map<uint64_t, std::unique_ptr<CModel>> Models;

	// Internal functions for model import
	void ProcessAssimpSceneMeshes(aiNode* Node, const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs);
	void ProcessAssimpSceneMaterials(const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs);

	bool IsExistingPath(std::filesystem::path* Path);
};