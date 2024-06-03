#pragma once



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
