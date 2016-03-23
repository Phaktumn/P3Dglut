#include "AABB.h"

IntersectData AABB::IntersectAABB(const AABB& other) const
{
	auto distances1 = other.GetMinExtents() - m_maxExtents;
	auto distances2 = m_minExtents - other.GetMaxExtents();
	auto distances = vec::Vector3::Max(distances1, distances2);

	float maxDistance = distances.Max();

	return IntersectData(maxDistance < 0, vec::Vector3(maxDistance));
}
