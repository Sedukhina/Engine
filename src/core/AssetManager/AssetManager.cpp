#include "AssetManager.h"
CAssetManager& CAssetManager::GetAssetManager()
{
	static CAssetManager AssetManger;
	return Renderer;
}

int CAssetManager::ImportMesh(CPath Path)
{
	return 0;
}
