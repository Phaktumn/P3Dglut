#include "BoxCollider.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider(vec::Vector3 &min, vec::Vector3 &max)
{
	this->max = max;
	this->min = min;
}

BoxCollider::~BoxCollider()
{
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppMemberFunctionMayBeStatic
bool BoxCollider::Intersects(BoxCollider* box)
{
	if ((this->max.x >= box->min.x) && (this->min.x <= box->max.x)) {
		if ((this->max.y < box->min.y) || (this->min.y > box->max.y)) {
			return false;
		}
		return ((this->max.z >= box->min.z) && (this->min.z <= box->max.z));
	}
	return false;
}

bool BoxCollider::Intersects(SphereCollider* sphere) const
{
	if (sphere->center.x - this->min.x > sphere->radius
		&& sphere->center.z - this->min.z > sphere->radius
		&& this->max.x - sphere->center.x > sphere->radius
		&& this->max.z - sphere->center.z > sphere->radius) {
		return true;
	}

	GLfloat dmin_lfloat = 0;
	if (sphere->center.x - this->min.x <= sphere->radius)
		dmin_lfloat += (sphere->center.x - this->min.x) * 
		(sphere->center.x - this->min.x);
	if (this->max.x - sphere->center.x <= sphere->radius)
		dmin_lfloat += (sphere->center.x - this->max.x) * 
		(sphere->center.x - this->max.x);

	//if (sphere->center.y - this->min.y <= sphere->radius)
	//	dmin_lfloat += (sphere->center.y - this->min.y) * (sphere->center.y - this->min.y);
	//else if (this->max.x - sphere->center.x <= sphere->radius)
	//	dmin_lfloat += (sphere->center.y - this->max.y) * (sphere->center.y - this->max.y);

	if (sphere->center.z - this->min.z <= sphere->radius)
		dmin_lfloat += (sphere->center.z - this->min.z) * (sphere->center.z - this->min.z);
	else if (this->max.x - sphere->center.x <= sphere->radius)
		dmin_lfloat += (sphere->center.z - this->max.z) * (sphere->center.z - this->max.z);

	if (dmin_lfloat <= sphere->radius * sphere->radius)
		return true;
	return false;
}

