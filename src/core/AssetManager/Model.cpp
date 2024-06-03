#pragma once

#include "Model.h"
#include "Logger.h"
#include "AssetManager.h"
#include "GetGameGlobals.h"

CModel::CModel(std::filesystem::path Path, std::string assetName, uint64_t mesh) 
	: Asset(Path, assetName), MeshID(mesh)
{
	
}

void CModel::SetMaterial(uint64_t Material)
{
	if (GetAssetManager().GetMaterial(Material))
	{
		MaterialID = Material;
	}
	else
	{
		LOG_ERROR("CModel::SetMaterial: No material was found with provided ID");
	}
}