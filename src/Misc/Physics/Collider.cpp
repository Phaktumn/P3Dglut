#include "Collider.h"
#include <iostream>
#include "BoundingSphere.h"

IntersectData Collider::Intersect(const Collider& other) const
{
	if(m_type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	std::cerr << "Error: Collisions not implemented between specified "
		<< "colliders." << std::endl;

	exit(1);
}
