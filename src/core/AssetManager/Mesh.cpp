#include "Mesh.h"


CMesh::CMesh(std::filesystem::path Path, std::string assetName, std::vector<Vertex>& vertices, std::vector<unsigned int> &indices)
	: Asset(Path, assetName), Vertices(vertices), Indices(indices)
{

}