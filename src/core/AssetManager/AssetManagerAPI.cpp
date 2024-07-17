#include "AssetManagerAPI.h"
#include "AssetManager.h"
#include "GetGameGlobals.h"

std::vector<uint64_t> ImportModel(std::filesystem::path Path)
{
	return GetAssetManager().ImportModel(Path);
}

uint64_t ImportTexture(std::filesystem::path Path)
{
	return GetAssetManager().ImportTexture(Path);
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

uint64_t GetDefaultMaterialGUID()
{
	return GetAssetManager().GetDefaultMaterialID();
}