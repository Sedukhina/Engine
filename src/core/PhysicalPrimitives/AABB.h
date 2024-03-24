#pragma once

#include <glm/glm.hpp>
#include "Primitive.h"

// Axis-aligned minimum bounding box
class CAABB : public IPrimitive
{
public:
	CAABB();
	~CAABB();

private:
	glm::vec3 Dimensions;
};
