#pragma once

#include "../../../Vars/vec3f.h"
#include "../IntersectData.h"
#include "../Collider.h"

class Plane;

class AABB : public Collider
{
public:
	AABB(const vec::Vector3& minExtents, const vec::Vector3& maxExtents): Collider(TYPE_AABB),
		m_initial_minExtents(minExtents),
		m_initial_maxExtents(maxExtents)
	{ }

	IntersectData IntersectAABB(const AABB& other) const;
	IntersectData IntersectPlane(const Plane& other) const;
	void Transform(const vec::Vector3& translation) override;

	const vec::Vector3& GetMinExtents() const{
		return m_minExtents;
	}

	const vec::Vector3& GetMaxExtents() const{
		return m_maxExtents;
	}

	vec::Vector3& GetCenter() const;

private:
	vec::Vector3 m_initial_minExtents;
	vec::Vector3 m_initial_maxExtents;
	vec::Vector3 m_minExtents;
	vec::Vector3 m_maxExtents;
};

