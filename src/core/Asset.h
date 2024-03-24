#pragma once
#define MAX_FILENAME_LENGTH 255

// Should be inherited by all assets classes 
class Asset {
	//GUID
	unsigned AssetID;
	char16_t Name[MAX_FILENAME_LENGTH];

protected:
	Asset();
	~Asset();
};