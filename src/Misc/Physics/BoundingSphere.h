#ifndef BOUNDING_SPHERE_INCLUDED_H
#define BOUNDING_SPHERE_INCLUDED_H

#pragma once
#include "Collider.h"

class Plane;

class BoundingSphere : public Collider
{
public:
	BoundingSphere(const vec::Vector3& center, float radius) :
		Collider(TYPE_SPHERE),
		m_radius(radius),
		m_center(center) { }
	~BoundingSphere();

	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;
	IntersectData IntersectPlane(Plane& other) const;
	virtual void Transform(const vec::Vector3& tranlation);
	vec::Vector3 GetCenter() const override;

	float getRadius() const { return m_radius; }

private:
	/** The center point of the sphere*/
	vec::Vector3 m_center;
	/** Radius itself brah*/
	float m_radius;
};

#endif


