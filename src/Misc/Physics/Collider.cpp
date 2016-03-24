#include "Collider.h"
#include <iostream>
#include "BoundingSphere.h"
#include "Mesh/AABB.h"

IntersectData Collider::Intersect(const Collider& other) const
{
	if(m_type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	if(m_type == TYPE_SPHERE && other.GetType() == TYPE_SIZE)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectPlane((Plane&)other);
	}

	if(m_type == TYPE_AABB && other.GetType() == TYPE_AABB)
	{
		AABB* self = (AABB*)this;
		return self->IntersectAABB((AABB&)other);
	}

	if (m_type == TYPE_AABB && other.GetType() == TYPE_SIZE)
	{
		AABB* self = (AABB*)this;
		return self->IntersectPlane((Plane&)other);
	}

	std::cerr << "Error: Collisions not implemented between specified "
		<< "colliders." << std::endl;

	exit(1);
}
