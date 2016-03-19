#pragma once
#include "gl/freeglut.h"
#include "../../Vars/vec3f.h"
#include "BoxCollider.h"

class BoxCollider;

class SphereCollider
{
public:
	SphereCollider();
	SphereCollider(vec::Vector3 *center, GLfloat radius);
	~SphereCollider();

	void Transform(vec::Vector3 *position);

	bool Intersects(BoxCollider *box);
	bool Intersects(SphereCollider *sphere);

	vec::Vector3 center;
	GLfloat radius;
};

