#include "Mesh.h"


CMesh::CMesh(std::filesystem::path Path, std::string assetName, std::vector<Vertex>& vertices, std::vector<unsigned int> &indices, CAABB Box)
	: Asset(Path, assetName), Vertices(vertices), Indices(indices), BoundingBox(Box)
{

}
