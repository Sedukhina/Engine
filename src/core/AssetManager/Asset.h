#pragma once
#include <filesystem>

// Should be inherited by all assets classes 
class Asset {
public:
	void SetName(std::string Name);

	std::string GetName();
	uint64_t GetAssetID();

	virtual void Load() { Loaded = true; };
	virtual void Unload() { Loaded = false; };
	bool IsLoaded();

protected:
	Asset(std::filesystem::path path, std::string assetName);
	~Asset() {};

private:
	Asset();
	uint64_t GenerateAssetID();

	// If(asset is in the asset manager library, but not used) then false
	bool Loaded = false;

	// GUID
	uint64_t AssetID;
	std::filesystem::path Path;
	std::string AssetName;
};