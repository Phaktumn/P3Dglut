#ifndef PLANE_INCLUDED_H
#define PLANE_INCLUDED_H

#pragma once
#include "../../P3Dglut/src/Vars/vec3f.h"
#include "../../Physics/IntersectData.h"
#include "../../Physics/BoundingSphere.h"

class Plane
{
public:
	Plane(const vec::Vector3& normal, float distance) :
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


