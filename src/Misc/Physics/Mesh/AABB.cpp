#include "AABB.h"
#include "Plane.h"
#include <iostream>

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	auto distances1 = other.GetMinExtents() - m_initial_maxExtents;
	auto distances2 = m_initial_minExtents - other.GetMaxExtents();
	auto distances = vec::Vector3::Max(distances1, distances2);
	auto maxDistance = distances.Max();
	return IntersectData(maxDistance < 0, vec::Vector3(maxDistance));
}

IntersectData AABB::IntersectPlane(const Plane& other) const
{
	auto Extence = (m_maxExtents - m_minExtents) / 2.0f;
	auto planeNormal = vec::Vector3::up();
	auto fRadius = abs(planeNormal.x * Extence.x) +
		abs(planeNormal.y * Extence.y) +
		abs(planeNormal.z * Extence.z);
	float s = planeNormal.Dot(GetCenter()) - Extence.y - 0.4;
	return IntersectData(abs(s) <= fRadius, planeNormal);
}

void AABB::Transform(const vec::Vector3& translation)
{
	m_minExtents = vec::Vector3(0, 0, 0);
	m_maxExtents = vec::Vector3(0, 0, 0);
	m_minExtents += translation + m_initial_minExtents;
	m_maxExtents += translation + m_initial_maxExtents;
	vec::Vector3 center = GetCenter();
}

vec::Vector3& AABB::GetCenter() const
{
	vec::Vector3 Extence = (m_maxExtents - m_minExtents) / 2.0f;
	vec::Vector3 CenterAABB = m_minExtents + Extence;
	return CenterAABB;
}
