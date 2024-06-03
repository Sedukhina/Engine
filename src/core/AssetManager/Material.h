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

	__declspec(dllexport) void SetTexture(uint64_t Texture, TextureType Type);
	__declspec(dllexport) void SetBaseColor(uint64_t baseColor);

	__declspec(dllexport) uint64_t GetBaseColor() { return BaseColor; };

private:
	uint64_t BaseColor = 0;
};
