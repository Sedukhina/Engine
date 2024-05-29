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
		if (Type == TextureType::Base)
		{
			SetBaseColor(Texture);
		}
	}
}

void CMaterial::SetBaseColor(uint64_t baseColor)
{
	if (GetAssetManager().IsExistingTexture(baseColor))
	{
		BaseColor = baseColor;
	}
}