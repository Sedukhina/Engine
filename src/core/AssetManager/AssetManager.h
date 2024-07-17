#pragma once

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

	// Returns created meshes IDs
	__declspec(dllexport) std::vector<uint64_t> ImportModel(std::filesystem::path Path);
	__declspec(dllexport) uint64_t ImportTexture(std::filesystem::path Path);

	__declspec(dllexport) bool IsExistingMesh(uint64_t ID);
	__declspec(dllexport) bool IsExistingTexture(uint64_t ID);
	__declspec(dllexport) bool IsExistingMaterial(uint64_t ID);

	__declspec(dllexport) CMesh* GetMesh(uint64_t ID);
	__declspec(dllexport) CTexture* GetTexture(uint64_t ID);
	__declspec(dllexport) CMaterial* GetMaterial(uint64_t ID);

	//
	//	Provides default material in case it's missing
	//
	uint64_t GetDefaultMaterialID();

private:
	//
	// Use count of each asset by ID
	// 
	std::map<uint64_t, int> UseCount;

	// TO DO: More effective memory allocation
	std::map<uint64_t, std::unique_ptr<CMesh>> Meshes;
	std::map<uint64_t, std::unique_ptr<CTexture>> Textures;
	std::map<uint64_t, std::unique_ptr<CMaterial>> Materials;

	// 
	//	Separately imports every mesh from assimp scene
	// 
	void ImportAssimpSceneMeshes(aiNode* Node, const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs, std::vector<uint64_t> &MaterialsIDs);

	void ImportAssimpSceneMaterials(const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs);


	//
	// Checks if path exists
	// If path is realtive to binary root turns path to absolute 
	//
	bool IsExistingPath(std::filesystem::path* Path);
};