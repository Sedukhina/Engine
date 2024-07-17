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
	Model,
	None
};
 
AssetType GetAssetType(std::filesystem::path Path)
{
	std::string Extension = Path.extension().string();
	for (int i = 0; i < TexturesExtensions.size(); i++)
	{
		if (!Extension.compare(TexturesExtensions[i]))
		{
			return Texture;
		}
	}
	for (int i = 0; i < ModelsExtensions.size(); i++)
	{
		if (!Extension.compare(ModelsExtensions[i]))
		{
			return Model;
		}
	}
	return None;
}

std::vector<uint64_t> CAssetManager::ImportModel(std::filesystem::path Path)
{
	// Checking if Path is valid path to 3d model
	if (Path.has_extension() && IsExistingPath(&Path) && GetAssetType(Path) == Model)
	{
		// Creating assimp importer to read scene from file
		Assimp::Importer Import;
		const aiScene* Scene = Import.ReadFile(Path.string().c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_GenBoundingBoxes );

		// Checking if loaded Models are valid
		if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
		{
			LOG_ERROR(Import.GetErrorString());
			return std::vector<uint64_t>{};
		}

		// Importing materials first so we can assign them when creating meshes
		std::vector<uint64_t> CreatedMaterialsIDs{};
		ImportAssimpSceneMaterials(Scene, Path, &CreatedMaterialsIDs);

		if (CreatedMaterialsIDs.empty())
		{
			CreatedMaterialsIDs.push_back(GetDefaultMaterialID());
		}

		std::vector<uint64_t> CreatedMeshesIDs{};
		ImportAssimpSceneMeshes(Scene->mRootNode, Scene, Path, &CreatedMeshesIDs, CreatedMaterialsIDs);

		return CreatedMeshesIDs;
	}
	return std::vector<uint64_t>{};
}


uint64_t CAssetManager::ImportTexture(std::filesystem::path Path)
{
	if (IsExistingPath(&Path) && GetAssetType(Path) == AssetType::Texture)
	{
		// TO DO: after asset serialization create functionality to store in diffrent dirs
		std::filesystem::path PathRealtiveToAssetFolder = "";

		// Checking if texture already exists
		std::string AssetName = Path.filename().string();
		auto TexturesIter = Textures.find(GenerateAssetID(PathRealtiveToAssetFolder, AssetName));
		if (TexturesIter == Textures.end())
		{
			int Width, Height, Channels;
			stbi_uc* Pixels = stbi_load(Path.string().c_str(), &Width, &Height, &Channels, 0);
			//unsigned char* Pixels = stbi_load(Path.string().c_str(), &Width, &Height, &Channels, 0);

			// Checking if texture succesfully loaded
			if (!Pixels)
			{
				LOG_ERROR("Failed to load texture file ");
				LOG_ERROR(Path.string().c_str());
				return 0;
			}

			std::vector<unsigned char> Img(Pixels, Pixels + Width * Height * Channels);
			CTexture Texture = CTexture(Path, AssetName, Img, Height, Width, Channels);
			Textures.emplace(Texture.GetAssetID(), std::make_unique<CTexture>(Texture));
			return Texture.GetAssetID();
		}
		else
		{
			char buffer[300];
			sprintf(buffer, "Texture with this name(%s) already exists in this directory, it will be used when for imported mesh.If want to create a new please rename or use another folder.", AssetName.c_str());
			LOG_WARNING(buffer);
		}
	}
	return 0;
}

bool CAssetManager::IsExistingMesh(uint64_t ID)
{
	auto MeshesIter = Meshes.find(ID);
	return MeshesIter == Meshes.end();
}

bool CAssetManager::IsExistingTexture(uint64_t ID)
{
	auto TexturesIter = Textures.find(ID);
	return TexturesIter != Textures.end();
}

bool CAssetManager::IsExistingMaterial(uint64_t ID)
{
	auto MaterialsIter = Materials.find(ID);
	return MaterialsIter != Materials.end();
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

// TO DO: Implement
uint64_t CAssetManager::GetDefaultMaterialID()
{
	return 0;
}

void CAssetManager::ImportAssimpSceneMeshes(aiNode* Node, const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedAssetsIDs, std::vector<uint64_t>& MaterialsIDs)
{
	// Meshes import
	for (unsigned int i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* AiMesh = Scene->mMeshes[Node->mMeshes[i]];

		// TO DO: after asset serialization create functionality to store in diffrent dirs
		std::filesystem::path PathRealtiveToAssetFolder = "";

		// Checking if mesh already exists
		std::string AssetName = AiMesh->mName.C_Str();
		auto MeshesIter = Meshes.find(GenerateAssetID(PathRealtiveToAssetFolder, AssetName));

		if (MeshesIter == Meshes.end())
		{
			// Indices import
			std::vector<unsigned int> Indices;
			Indices.reserve(3 * AiMesh->mNumFaces);
			for (unsigned int i = 0; i < AiMesh->mNumFaces; i++)
			{
				aiFace face = AiMesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					Indices.push_back(face.mIndices[j]);
			}

			// Vertices import
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

			// Creating axis aligned bounding box for mesh 
			CAABB Box = CAABB(AiMesh->mAABB.mMin.x, AiMesh->mAABB.mMin.y, AiMesh->mAABB.mMin.z, AiMesh->mAABB.mMax.x, AiMesh->mAABB.mMax.y, AiMesh->mAABB.mMax.z);

			CMesh Mesh = CMesh(Path, PathRealtiveToAssetFolder, AssetName, Vertices, Indices, Box);

			int MaterialIndex = AiMesh->mMaterialIndex;
			if (MaterialIndex < MaterialsIDs.size())
			{
				Mesh.SetMaterial(MaterialsIDs[MaterialIndex], 0);
			}
			else
			{
				Mesh.SetMaterial(GetDefaultMaterialID(), 0);
			}

			CreatedAssetsIDs->emplace_back(Mesh.GetAssetID());
			Meshes.emplace(Mesh.GetAssetID(), std::make_unique<CMesh>(Mesh));
		}
		else
		{
			// TO DO: Add Reimport function after serialization
			LOG_WARNING("Mesh with this name already exists in this directory. If you want to reimport... ");
		}
	}

	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		ImportAssimpSceneMeshes(Node->mChildren[i], Scene, Path, CreatedAssetsIDs, MaterialsIDs);
	}
}

void CAssetManager::ImportAssimpSceneMaterials(const aiScene* Scene, std::filesystem::path Path, std::vector<uint64_t>* CreatedMaterialsIDs)
{
	std::filesystem::path PathRealtiveToAssetFolder = "";

	for (unsigned int m = 0; m < Scene->mNumMaterials; m++)
	{
		aiMaterial* AiMaterial = Scene->mMaterials[m];

		aiString materialName;
		aiReturn ret = AiMaterial->Get(AI_MATKEY_NAME, materialName);
		// If material name is absent throwing error
		if (ret != AI_SUCCESS)
		{
			LOG_ERROR("Can`t read material name");
			// Adding 0, so material indices will be valid while adding materials to meshes
			CreatedMaterialsIDs->push_back(0);
		}
		else
		{
			// Checking if material already exists
			std::string AssetName = materialName.C_Str();
			auto MaterialsIter = Materials.find(GenerateAssetID(PathRealtiveToAssetFolder, AssetName));
			if (MaterialsIter == Materials.end())
			{
				// Creating empty material
				CMaterial Material = CMaterial(materialName.C_Str());

				// Checking if material has diffuse textures
				// In case multiple textures only first will be taken
				if(AiMaterial->GetTextureCount(aiTextureType_DIFFUSE))
				{
					aiString textureName;
					ret = AiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);
					if (ret != AI_SUCCESS)
					{
						LOG_ERROR("Can`t read diffuse texture name");
					}
					else
					{
						std::filesystem::path TexturePath(Path.parent_path().string());
						TexturePath.append(textureName.data);
						uint64_t TexID = ImportTexture(TexturePath);
						if (TexID)
						{
							Material.SetDiffuseTexture(TexID);
						}
						else
						{
							char buffer[300];
							sprintf(buffer, "Texture not found: %s", TexturePath.string().c_str());
							LOG_ERROR(buffer);
						}
					}
				}

				// Pushing material to asset library
				CreatedMaterialsIDs->emplace_back(Material.GetAssetID());
				Materials.emplace(Material.GetAssetID(), std::make_unique<CMaterial>(Material));
			}
			else
			{
				char buffer[300];
				sprintf(buffer, "Material with this name(%s) already exists in this directory, it will be used when for imported mesh.If want to create a new please rename or use another folder.", materialName.C_Str());
				LOG_WARNING(buffer);
				CreatedMaterialsIDs->push_back(GenerateAssetID(PathRealtiveToAssetFolder, AssetName));
			}
		}
	}
}


bool CAssetManager::IsExistingPath(std::filesystem::path* Path)
{
	// Checking path in case it's absolute
	if (!std::filesystem::exists(Path->string()))
	{
		// Checking path in case it's realtive tp engine asset dir
		std::string root(TO_STRING(ENGINE_ASSET_DIR));
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

