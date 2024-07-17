#include "Level.h"

CLevel::CLevel(std::string LevelName)
{
	Name = LevelName;
	Octree = COctree();
}
