#include "Plane.h"

Plane Plane::Normalized() const
{
	float magni_f = m_normal.length();
	return Plane(m_normal / magni_f, m_distance / magni_f);
}

IntersectData Plane::IntersectSphere(const BoundingSphere& other)
{
	float distanceFromSphereCenter =
		// ReSharper disable once CppMsExtBindingRValueToLvalueReference
		float(fabs(vec::Vector3::Dot(m_normal, other.GetCenter()) + m_distance));
	float distanceFromSphere = distanceFromSphereCenter - other.getRadius();
	return IntersectData(distanceFromSphere < 0, m_normal * distanceFromSphere);
}
