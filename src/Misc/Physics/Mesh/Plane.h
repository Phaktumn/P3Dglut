#ifndef PLANE_INCLUDED_H
#define PLANE_INCLUDED_H

#pragma once
#include <Vars/vec3f.h>
#include <Misc/Physics/IntersectData.h>
#include <Misc/Physics/BoundingSphere.h>

class Plane : public Collider
{
public:
	Plane(vec::Vector3 normal, float distance) : Collider(TYPE_SIZE),
		m_distance(distance),
		m_normal(normal) {}

	Plane Normalized() const;
	IntersectData IntersectSphere(const BoundingSphere& other);

	const vec::Vector3& GetNormal() const { return m_normal; }
	float GetDistance()             const { return m_distance; }

private:
	float m_distance;
	vec::Vector3 m_normal;
};

#endif


