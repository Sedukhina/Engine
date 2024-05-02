#pragma once

#include "Mesh.h"
#include "Path.h"

class CAssetManager {
public:
	static CAssetManager& GetAssetManager();

	int ImportMesh(CPath Path);

private:
	CAssetManager() {};
	~CAssetManager() {};
};