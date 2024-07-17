#pragma once

// 
//	Class for axis aligned bounding boxes used for building level octree
//
class CAABB
{
public:
	CAABB(float x, float y, float z, float X, float Y, float Z);

	~CAABB() {};

private:
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;
};
