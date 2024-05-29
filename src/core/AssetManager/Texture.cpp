#include "Texture.h"

CTexture::CTexture(std::filesystem::path Path, std::string assetName, std::vector<unsigned char> img, int height, int width, int nChannels)
	: Asset(Path, assetName), Image(img), ImageHeight(height), ImageWidth(width), NumChannels(nChannels)
{

}
