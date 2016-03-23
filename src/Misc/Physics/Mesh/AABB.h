#pragma once

#include "../../../Vars/vec3f.h"
#include "../IntersectData.h"

class AABB
{
public:
	AABB(const vec::Vector3& minExtents, const vec::Vector3& maxExtents):
		m_minExtents(minExtents),
		m_maxExtents(maxExtents)
	{
	}

	IntersectData IntersectAABB(const AABB& other) const;

	const vec::Vector3& GetMinExtents() const
	{
		return m_minExtents;
	}

	const vec::Vector3& GetMaxExtents() const
	{
		return m_maxExtents;
	}

private:
	const vec::Vector3 m_minExtents;
	const vec::Vector3 m_maxExtents;
};

