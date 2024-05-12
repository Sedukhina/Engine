#include "Asset.h"
#include "Asset.h"
#include "..\Logger.h"

#define STRING(x) #x
#define TO_STRING(x) STRING(x)

void Asset::SetName(std::string Name)
{
}

std::string Asset::GetName()
{ 
	return AssetName; 
}

uint64_t Asset::GetAssetID()
{
	return AssetID;
}

uint64_t Asset::GenerateAssetID()
{
	std::filesystem::path PathWithName{};
	PathWithName.append(Path.string());
	PathWithName.append(AssetName);
	uint64_t ID = std::hash<std::filesystem::path>{}(Path);
	return ID;
}

Asset::Asset(std::filesystem::path path, std::string assetName) : Path(path)
{
	if (Path.is_absolute())
	{
		Path = std::filesystem::relative(Path, TO_STRING(BIN_ROOT));
	}
	AssetID = GenerateAssetID();
}
