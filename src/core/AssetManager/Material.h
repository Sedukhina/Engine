#pragma once

#include "Asset.h"

enum TextureType
{
	Diffuse
};

class CTexture;

class CMaterial : public Asset
{
public:
	CMaterial(std::string assetName);
	~CMaterial() {};

	__declspec(dllexport) void SetTexture(uint64_t Texture, TextureType Type);
	__declspec(dllexport) void SetDiffuseTexture(uint64_t Texture);

	__declspec(dllexport) CTexture* GetDiffuseTexture();
	__declspec(dllexport) uint64_t GetDiffuseTextureGUID() { return DiffuseTexture; };

private:

	uint64_t DiffuseTexture = 0;
};
