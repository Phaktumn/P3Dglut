#include "SphereCollider.h"


SphereCollider::SphereCollider(): radius(0)
{
}

SphereCollider::SphereCollider(vec::Vector3 *center, GLfloat radius)
{
	this->center.x = center->x;
	this->center.y = center->y;
	this->center.z = center->z;
	this->radius = radius;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Transform(vec::Vector3* vec)
{
	this->center.x = vec->x;
	this->center.y = vec->y;
	this->center.z = vec->z;
}

bool SphereCollider::Intersects(BoxCollider* box)
{
	return box->Intersects(this);
}

bool SphereCollider::Intersects(SphereCollider* sphere)
{
	GLfloat sqDistance;
	sqDistance = vec::Vector3::DistanceSquared(sphere->center, this->center);
	if (sqDistance > (sphere->radius + this->radius) * (sphere->radius + this->radius))
		return true;
	return false;
}
