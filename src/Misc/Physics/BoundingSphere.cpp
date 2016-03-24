#include "BoundingSphere.h"
#include "IntersectData.h"
#include "Mesh/Plane.h"

BoundingSphere::~BoundingSphere()
{
}

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
	float radiusDistance = m_radius + other.getRadius();
	vec::Vector3 direction = (other.GetCenter() - m_center);
	float centerDistance = direction.length();
	direction = direction / centerDistance;

	float distance = centerDistance - radiusDistance;

	return IntersectData(distance < 0, direction * distance);
}

IntersectData BoundingSphere::IntersectPlane(Plane& other) const
{
	return other.IntersectSphere(*this);
}

void BoundingSphere::Transform(const vec::Vector3& translation)
{
	m_center += translation;
}

vec::Vector3 BoundingSphere::GetCenter() const
{ return m_center; }
