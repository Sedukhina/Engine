#pragma once

#include "Asset.h"

enum TextureType
{
	Base
};

class CMaterial : public Asset
{
public:
	CMaterial(std::string assetName);
	~CMaterial() {};

	void SetTexture(uint64_t Texture, TextureType Type);
	void SetBaseColor(uint64_t baseColor);

	uint64_t GetBaseColor() { return BaseColor; };

private:
	uint64_t BaseColor;
};
