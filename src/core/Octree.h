#include "Box.h"
#include "Object.h"

class COctree
{
public:
	COctree() {};
	~COctree() {};

private:
	CAABB Box;

	std::vector<COctree> SubTrees;
	std::vector<CSceneObject> Objects;
};
