#include "Texture.h"
#include "Material.h"
#include "GetGameGlobals.h"
#include "AssetManager.h"

CMaterial::CMaterial(std::string assetName) : Asset("", assetName)
{

}

void CMaterial::SetTexture(uint64_t Texture, TextureType Type)
{
	if (GetAssetManager().IsExistingTexture(Texture))
	{
		if (Type == TextureType::Diffuse)
		{
			SetDiffuseTexture(Texture);
		}
	}
}

void CMaterial::SetDiffuseTexture(uint64_t Texture)
{
	if (GetAssetManager().IsExistingTexture(Texture))
	{
		DiffuseTexture = Texture;
	}
}

CTexture* CMaterial::GetDiffuseTexture()
{
	return GetAssetManager().GetTexture(DiffuseTexture);
}