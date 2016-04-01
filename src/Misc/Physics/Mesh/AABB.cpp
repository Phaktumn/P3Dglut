#include "AABB.h"
#include "Plane.h"

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	vec::Vector3 distances1 = other.GetMinExtents() - m_maxExtents;
	vec::Vector3 distances2 = m_minExtents - other.GetMaxExtents();
	vec::Vector3 distances = vec::Vector3::Max(distances1, distances2);
	float maxDistance = distances.Max();
	return IntersectData(maxDistance < 0, vec::Vector3(maxDistance, 0, maxDistance));
}

IntersectData AABB::IntersectPlane(const Plane& other) const
{
    vec::Vector3 Extence = (m_maxExtents - m_minExtents) / 2.0f;
	vec::Vector3 planeNormal = other.GetNormal();
	float fRadius = abs(planeNormal.x * Extence.x) +
		abs(planeNormal.y * Extence.y) +
		abs(planeNormal.z * Extence.z);
	float s = planeNormal.Dot(GetCenter()) - other.GetDistance();
	return IntersectData(abs(s) <= fRadius, planeNormal);
}

void AABB::Transform(const vec::Vector3& translation)
{
	m_minExtents = m_initial_minExtents + translation;
	m_maxExtents = m_initial_maxExtents + translation;
	vec::Vector3 center = GetCenter();
}

vec::Vector3& AABB::GetCenter() const
{
	vec::Vector3 Extence = (m_maxExtents - m_minExtents) / 2.0f;
	vec::Vector3 CenterAABB = m_minExtents + Extence;
	return CenterAABB;
}
