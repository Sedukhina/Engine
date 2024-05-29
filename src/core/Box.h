#pragma once

class CBox
{
public:
	CBox(float x, float y, float z, float X, float Y, float Z);
	~CBox() {};

private:
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;
};
