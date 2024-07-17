#pragma once
#include <filesystem>

extern uint64_t GenerateAssetID(std::filesystem::path Path, std::string AssetName);

//
// Should be inherited by all assets classes
// 
class Asset {
public:

	void SetName(std::string Name);

	std::string GetName();
	uint64_t GetAssetID();

	bool IsLoaded();

protected:
	//Only changes IsLoaded status to True
	virtual void Load();
	//Only changes IsLoaded status to False
	virtual void Unload();

	Asset(std::filesystem::path path, std::string assetName);
	~Asset() {};

	// Used after changing asset name or asset location
	void UpdateAssetID();

private:
	Asset();

	//
	// If asset is loaded in memory 
	//
	bool Loaded = false;

	// GUID
	uint64_t AssetID;

	//
	// Relative path to asset in asset folder 
	//
	std::filesystem::path Path;
	std::string AssetName;
};