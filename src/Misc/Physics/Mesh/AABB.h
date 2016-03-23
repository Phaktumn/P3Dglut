#pragma once

#include "../../../Vars/vec3f.h"
#include "../IntersectData.h"

namespace vec {
	class AABB
	{
	public:
		AABB(const Vector3& minExtents, const Vector3& maxExtents):
			m_minExtents(minExtents),
			m_maxExtents(maxExtents){}

		IntersectData IntersectAABB(const AABB& other) const;

		const Vector3& GetMinExtents() const { return m_minExtents; }
		const Vector3& GetMaxExtents()const { return m_maxExtents; }

	private:
		const Vector3 m_minExtents;
		const Vector3 m_maxExtents;
	};
}

