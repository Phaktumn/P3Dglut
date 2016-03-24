#include "AABB.h"
#include "Plane.h"

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	auto distances1 = other.GetMinExtents() - m_maxExtents;
	auto distances2 = m_minExtents - other.GetMaxExtents();
	auto distances = vec::Vector3::Max(distances1, distances2);

	float maxDistance = distances.Max();

	return IntersectData(maxDistance < 0, vec::Vector3(maxDistance));
}

IntersectData AABB::IntersectPlane(const Plane& other) const
{
	vec::Vector3 Extence = (m_maxExtents - m_minExtents) / 2.0f;
	vec::Vector3 CenterAABB = m_minExtents + Extence;
	vec::Vector3 planeNormal = other.GetNormal();

	float fRadius = abs(planeNormal.x * Extence.x) +
		abs(planeNormal.y * Extence.y) +
		abs(planeNormal.z * Extence.z);
	float s = other.GetNormal().Dot(CenterAABB) - other.GetDistance();

	return IntersectData(abs(s) <= fRadius, other.GetNormal());
	//return IntersectData(false, other.GetNormal());
}


void AABB::Transform(const vec::Vector3& translation)
{
	m_minExtents += translation;
	m_maxExtents += translation;
}
