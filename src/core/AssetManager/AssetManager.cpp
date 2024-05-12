#include <assimp/Importer.hpp> 
#include <assimp/scene.h>    
#include <assimp/postprocess.h> 

#include "AssetManager.h"
#include "../Logger.h"
 

#define STRING(x) #x
#define TO_STRING(x) STRING(x)

const char StringExtensions[][5] = { ".fbx" };

CAssetManager::CAssetManager()
{

}

std::vector<uint64_t> CAssetManager::ImportModel(std::filesystem::path Path)
{
	if (Path.has_extension() && IsExistingPath(&Path))
	{
		Assimp::Importer Import;
		const aiScene* Scene = Import.ReadFile(Path.string().c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
		{
			LOG_ERROR(Import.GetErrorString());
			return std::vector<uint64_t>{};
		}

		std::vector<uint64_t> CreatedAssetsIDs{};
		CreatedAssetsIDs.reserve(Scene->mNumMeshes);
		ProcessAssimpScene(Scene->mRootNode, Scene, Path, &CreatedAssetsIDs);
	}
	return std::vector<uint64_t>();
}

CMesh* CAssetManager::GetMesh(uint64_t ID)
{
	return Meshes[ID].get();
}

CMesh* CAssetManager::GetMesh()
{
	return Meshes[17892047228360777561].get();
	//return Meshes[837288501381251621].get();
}


void CAssetManager::ProcessAssimpScene(aiNode* Node, const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs)
{
	for (unsigned int i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* AiMesh = Scene->mMeshes[Node->mMeshes[i]];

		std::vector<unsigned int> Indices;
		Indices.reserve(3 * AiMesh->mNumFaces);
		for (unsigned int i = 0; i < AiMesh->mNumFaces; i++)
		{
			aiFace face = AiMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				Indices.push_back(face.mIndices[j]);
		}

		std::vector<float> Vertices;
		Vertices.reserve(8 * AiMesh->mNumVertices);
		for (unsigned int i = 0; i < AiMesh->mNumVertices; i++)
		{
			Vertices.push_back(AiMesh->mVertices[i].x);
			Vertices.push_back(AiMesh->mVertices[i].y);
			Vertices.push_back(AiMesh->mVertices[i].z);

			Vertices.push_back(AiMesh->mNormals[i].x);
			Vertices.push_back(AiMesh->mNormals[i].y);
			Vertices.push_back(AiMesh->mNormals[i].z);

			if (AiMesh->mTextureCoords[0])
			{
				Vertices.push_back(AiMesh->mTextureCoords[0][i].x);
				Vertices.push_back(AiMesh->mTextureCoords[0][i].y);
			}
		}
		
		CMesh Mesh =  CMesh(Path, AiMesh->mName.C_Str(), Vertices, Indices);
		Meshes.emplace(Mesh.GetAssetID(), std::make_unique<CMesh>(Mesh));
	}

	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		ProcessAssimpScene(Node->mChildren[i], Scene, Path, CreatedAssetsIDs);
	}
}

bool CAssetManager::IsExistingPath(std::filesystem::path* Path)
{
	if (!std::filesystem::exists(Path->string()))
	{
		std::string root(TO_STRING(BIN_ROOT));
		std::filesystem::path AbsPath(root);
		AbsPath += Path->string();
		if (!std::filesystem::exists(AbsPath))
		{
			LOG_ERROR("Provided path to asset doesn't exist: ");
			LOG_ERROR(Path->string().c_str());
			LOG_ERROR(AbsPath.string().c_str());
			return false;
		}
		Path->swap(AbsPath);
	}
	return true;
}

