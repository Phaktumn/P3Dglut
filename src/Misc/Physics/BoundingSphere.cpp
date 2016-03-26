#include "BoundingSphere.h"
#include "IntersectData.h"
#include "Mesh/Plane.h"

BoundingSphere::~BoundingSphere()
{
	m_center = vec::Vector3::zero();
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

vec::Vector3& BoundingSphere::GetCenter() const
// ReSharper disable once CppMsExtBindingRValueToLvalueReference
{ return vec::Vector3(m_center.x, m_center.y, m_center.z); }
