#include "Asset.h"
#include "Asset.h"
#include "..\Logger.h"

#define STRING(x) #x
#define TO_STRING(x) STRING(x)

uint64_t GenerateAssetID(std::filesystem::path Path, std::string AssetName)
{
	std::filesystem::path PathWithName{};
	PathWithName.append(Path.string());
	PathWithName.append(AssetName);
	uint64_t ID = std::hash<std::filesystem::path>{}(PathWithName);
	return ID;
}

bool Asset::IsLoaded()
{
	return Loaded;
}

void Asset::SetName(std::string Name)
{
	AssetName = Name;
	UpdateAssetID();
}

std::string Asset::GetName()
{ 
	return AssetName; 
}

uint64_t Asset::GetAssetID()
{
	return AssetID;
}

void Asset::UpdateAssetID()
{
	AssetID = GenerateAssetID(Path, AssetName);
}

void Asset::Load()
{
	Loaded = true;
}

void Asset::Unload()
{
	Loaded = false;
}

Asset::Asset(std::filesystem::path path, std::string assetName) : Path(path), AssetName(assetName)
{
	if (Path.is_absolute())
	{
		Path = std::filesystem::relative(Path, TO_STRING(BIN_ROOT));
	}
	UpdateAssetID();
}
