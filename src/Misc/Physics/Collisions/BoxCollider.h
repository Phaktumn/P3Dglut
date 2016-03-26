#include "gl/freeglut.h"
#include "../../../Vars/vec3f.h"

#pragma once
class SphereCollider;

namespace vec{
	class Vector3;
}

class BoxCollider
{
public:
	BoxCollider(vec::Vector3 &min, vec::Vector3 &max);
	~BoxCollider();

	bool Intersects(BoxCollider* box);
	bool Intersects(SphereCollider* sphere) const;

	const GLuint CornerCount = 8;
	
	vec::Vector3 min;
	vec::Vector3 max;
};

