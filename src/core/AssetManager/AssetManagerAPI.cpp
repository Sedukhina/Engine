#include "AssetManagerAPI.h"
#include "AssetManager.h"
#include "GetGameGlobals.h"

std::vector<std::vector<uint64_t>> ImportModel(std::filesystem::path Path)
{
	return GetAssetManager().ImportModel(Path);
}

uint64_t ImportTexture(std::filesystem::path Path)
{
	return GetAssetManager().ImportTexture(Path);
}

uint64_t CreateMaterial(std::string Name)
{
	return GetAssetManager().CreateMaterial(Name);
}

void SetTextureForMaterial(uint64_t Texture, uint64_t Material, TextureType Type)
{
	CMaterial* Mat = GetMaterial(Material);
	if (Mat)
	{
		Mat->SetTexture(Texture, Type);
	}
}

CMesh* GetMesh(uint64_t ID)
{
	return GetAssetManager().GetMesh(ID);
}

CTexture* GetTexture(uint64_t ID)
{
	return GetAssetManager().GetTexture(ID);
}

CMaterial* GetMaterial(uint64_t ID)
{
	return GetAssetManager().GetMaterial(ID);
}

CModel* GetModel(uint64_t ID)
{
	return GetAssetManager().GetModel(ID);
}