#include "Mesh.h"
#include "Logger.h"
#include "AssetManagerAPI.h"

CMesh::CMesh(std::filesystem::path Source, std::filesystem::path Path, std::string assetName, std::vector<Vertex>& vertices, std::vector<unsigned int> &indices, CAABB Box)
	: Asset(Path, assetName), Vertices(vertices), Indices(indices), BoundingBox(Box), SourcePath(Source)
{
	// Asset is marked loaded after import
	Asset::Load();
	SetMaterial(GetDefaultMaterialGUID(), 0);
}

void CMesh::SetMaterial(uint64_t material, int MaterialIndex)
{
	if (MaterialIndex == 0)
	{
		Material_0 = material;
	}
	else if (MaterialsAmount > 1 && MaterialIndex == 1)
	{
		Material_1 = material;
	}
	else if (MaterialsAmount == 3 && MaterialIndex == 2)
	{
		Material_2 = material;
	}
	else
	{
		LOG_WARNING("Material index is out of range");
	}
}

void CMesh::AddMaterialSlot()
{
	if (MaterialsAmount < 3)
	{
		MaterialsAmount += 1;
	}
	else
	{
		LOG_WARNING("Can't increase materials amount, the limit is 3");
	}
}

void CMesh::DeleteMaterialSlot()
{
	if (MaterialsAmount > 1)
	{
		MaterialsAmount -= 1;
	}
	else
	{
		LOG_WARNING("Can't delete an only material");
	}
}

std::filesystem::path CMesh::GetSourcePath()
{
	return SourcePath;
}