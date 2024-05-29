#pragma once

#include "Asset.h"

class CTexture : public Asset
{
public:
	CTexture(std::filesystem::path Path, std::string assetName, std::vector<unsigned char> img, int height, int width, int nChannels) ;
	~CTexture() {};

	int GetWidth() { return ImageWidth; };
	int GetHeight() { return ImageHeight; };
	int GetNumChannels() { return NumChannels; };
	const unsigned char* GetPixels() { return &Image[0]; };

private:
	const std::vector<unsigned char> Image;
	int ImageHeight;
	int ImageWidth;
	int NumChannels;
};
