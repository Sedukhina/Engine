#include "Box.h"
#include "Object.h"

class COctree
{
public:
	COctree() {};
	~COctree() {};

private:
	CBox Box;

	std::vector<COctree> SubTrees;
	std::vector<CSceneObject> Objects;
};
