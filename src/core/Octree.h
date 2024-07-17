#include "AABB.h"
#include "Object.h"

class COctree
{
public:
	// Creates null Octree
	COctree();
	~COctree() {};

private:
	CAABB Box;

	std::vector<COctree> SubTrees;
	std::vector<CSceneObject> Objects;
};
