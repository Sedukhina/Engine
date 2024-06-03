#include <assimp/Importer.hpp> 
#include <assimp/scene.h>    
#include <assimp/postprocess.h> 

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "AssetManager.h"
#include "../Logger.h"

#define STRING(x) #x
#define TO_STRING(x) STRING(x)

const std::vector<std::string> ModelsExtensions = { ".fbx", ".obj"};
const std::vector<std::string> TexturesExtensions = { ".png", ".jpg"};

enum AssetType
{
	Texture,
	Material,
	Mesh, 
	None
};
 
AssetType GetAssetType(std::filesystem::path Path)
{
	std::string Extension = Path.extension().string();
	for (int i = 0; i < TexturesExtensions.size(); i++)
	{
		if (Extension.compare(TexturesExtensions[i]))
		{
			return Texture;
		}
	}
	return None;
}

std::vector<std::vector<uint64_t>> CAssetManager::ImportModel(std::filesystem::path Path)
{
	if (Path.has_extension() && IsExistingPath(&Path))
	{
		Assimp::Importer Import;
		const aiScene* Scene = Import.ReadFile(Path.string().c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_GenBoundingBoxes);

		if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
		{
			LOG_ERROR(Import.GetErrorString());
			return std::vector<std::vector<uint64_t>>{};
		}

		std::vector<uint64_t> CreatedMeshesIDs{};
		ProcessAssimpSceneMeshes(Scene->mRootNode, Scene, Path, &CreatedMeshesIDs);
		std::vector<uint64_t> CreatedMaterialsIDs{};
		ProcessAssimpSceneMaterials(Scene, Path, &CreatedMaterialsIDs);
		std::vector<uint64_t> CreatedModelsIDs{};
		for (size_t i = 0; i < CreatedMeshesIDs.size(); i++)
		{
			std::string Name = "Model_";
			CModel Model = CModel(Path, Name.append(GetMesh(CreatedMeshesIDs[i])->GetName()), CreatedMeshesIDs[i]);
			if (CreatedMaterialsIDs.size() > i)
			{
				Model.SetMaterial(CreatedMaterialsIDs[i]);
			}
			CreatedModelsIDs.emplace_back(Model.GetAssetID());
			Models.emplace(Model.GetAssetID(), std::make_unique<CModel>(Model));
		}
		return std::vector<std::vector<uint64_t>>{CreatedModelsIDs, CreatedMeshesIDs, CreatedMaterialsIDs};
	}
	return std::vector<std::vector<uint64_t>>{};
}


uint64_t CAssetManager::ImportTexture(std::filesystem::path Path)
{
	if (IsExistingPath(&Path) && GetAssetType(Path) == AssetType::Texture)
	{
		int Width, Height, Channels;

		stbi_uc* Pixels = stbi_load(Path.string().c_str(), &Width, &Height, &Channels, 0);
		//unsigned char* Pixels = stbi_load(Path.string().c_str(), &Width, &Height, &Channels, 0);

		if (!Pixels) 
		{
			LOG_ERROR("Failed to load texture file ");
			LOG_ERROR(Path.string().c_str());
			return 0;
		}

		std::vector<unsigned char> Img(Pixels, Pixels + Width * Height * Channels);
		CTexture Texture = CTexture(Path, Path.filename().string(), Img, Height, Width, Channels);
		Textures.emplace(Texture.GetAssetID(), std::make_unique<CTexture>(Texture));
		return Texture.GetAssetID();
	}
	return 0;
}

bool CAssetManager::IsExistingMesh(uint64_t ID)
{
	return Meshes.count(ID) > 0;
}

bool CAssetManager::IsExistingTexture(uint64_t ID)
{
	return Textures.count(ID) > 0;
}

bool CAssetManager::IsExistingMaterial(uint64_t ID)
{
	return Materials.count(ID) > 0;
}

bool CAssetManager::IsExistingModel(uint64_t ID)
{
	return Models.count(ID) > 0;
}

uint64_t CAssetManager::CreateMaterial(std::string Name)
{
	CMaterial Material = CMaterial(Name);
	uint64_t ID = Material.GetAssetID();
	auto MaterialsIter = Materials.find(ID);
	if (MaterialsIter != Materials.end())
	{
		LOG_ERROR("CAssetManager::CreateMaterial: Failed to create material. Asset name already taken."); 
		return 0;
	}
	Materials.emplace(Material.GetAssetID(), std::make_unique<CMaterial>(Material));
	return ID;
}

CMesh* CAssetManager::GetMesh(uint64_t ID)
{
	auto MeshesIter = Meshes.find(ID);
	if (MeshesIter != Meshes.end())
	{
		return MeshesIter->second.get();
	}
	return 0;
}

CTexture* CAssetManager::GetTexture(uint64_t ID)
{
	auto TexturesIter = Textures.find(ID);
	if (TexturesIter != Textures.end())
	{
		return TexturesIter->second.get();
	}
	return 0;
}

CMaterial* CAssetManager::GetMaterial(uint64_t ID)
{
	auto MaterialsIter = Materials.find(ID);
	if (MaterialsIter != Materials.end())
	{
		return MaterialsIter->second.get();
	}
	return 0;
}

CModel* CAssetManager::GetModel(uint64_t ID)
{
	auto ModelsIter = Models.find(ID);
	if (ModelsIter != Models.end())
	{
		return ModelsIter->second.get();
	}
	return 0;
}

void CAssetManager::ProcessAssimpSceneMeshes(aiNode* Node, const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs)
{
	// Meshes import
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

		std::vector<Vertex> Vertices;
		Vertices.reserve(AiMesh->mNumVertices);
		for (unsigned int i = 0; i < AiMesh->mNumVertices; i++)
		{
			Vertex Vert;

			Vert.PositionX = AiMesh->mVertices[i].x;
			Vert.PositionY = AiMesh->mVertices[i].y;
			Vert.PositionZ = AiMesh->mVertices[i].z;

			Vert.NormalX = AiMesh->mNormals[i].x;
			Vert.NormalX = AiMesh->mNormals[i].y;
			Vert.NormalX = AiMesh->mNormals[i].z;

			if (AiMesh->mTextureCoords[0])
			{
				Vert.TextureCoordinateX = AiMesh->mTextureCoords[0][i].x;
				Vert.TextureCoordinateY = AiMesh->mTextureCoords[0][i].y;
			}

			Vertices.push_back(Vert);
		}
		
		CAABB Box = CAABB(AiMesh->mAABB.mMin.x, AiMesh->mAABB.mMin.y, AiMesh->mAABB.mMin.z, AiMesh->mAABB.mMax.x, AiMesh->mAABB.mMax.y, AiMesh->mAABB.mMax.z);

		CMesh Mesh =  CMesh(Path, AiMesh->mName.C_Str(), Vertices, Indices, Box);
		CreatedAssetsIDs->emplace_back(Mesh.GetAssetID());
		Meshes.emplace(Mesh.GetAssetID(), std::make_unique<CMesh>(Mesh));
	}

	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		ProcessAssimpSceneMeshes(Node->mChildren[i], Scene, Path, CreatedAssetsIDs);
	}
}

void CAssetManager::ProcessAssimpSceneMaterials(const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs)
{
	for (unsigned int m = 0; m < Scene->mNumMaterials; m++)
	{
		aiMaterial* AiMaterial = Scene->mMaterials[m];
		//The name of the material found in mesh file
		aiString materialName;
		//Code which says whether loading something has been successful of not
		aiReturn ret = AiMaterial->Get(AI_MATKEY_NAME, materialName);
		if (ret != AI_SUCCESS)
		{
			char buffer[100];
			sprintf(buffer, "Material_%d", m);
			materialName = buffer;
		}
		 
		CMaterial Material = CMaterial(materialName.C_Str());

		for (unsigned int t = 0; t < AiMaterial->GetTextureCount(aiTextureType_DIFFUSE); t++)
		{
			aiString textureName;
			ret = AiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);
			std::filesystem::path TexturePath(Path.parent_path().string());
			TexturePath.append(textureName.data);
			uint64_t TexID = ImportTexture(TexturePath);
			if (TexID)
			{
				CreatedAssetsIDs->emplace_back(TexID);
			}
			else
			{
				char buffer[300];
				sprintf(buffer, "Texture not found: %s", TexturePath.string().c_str());
				LOG_ERROR(buffer);
			}
		}
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

