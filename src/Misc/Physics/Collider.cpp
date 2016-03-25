#include "Collider.h"
#include "BoundingSphere.h"
#include "Mesh/AABB.h"
#include "../src/Misc/Debug/IO.h"

IntersectData Collider::Intersect(const Collider& other) const
{
	if(m_type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE)
	{
		auto self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	if(m_type == TYPE_SPHERE && other.GetType() == TYPE_SIZE)
	{
		auto self = (BoundingSphere*)this;
		return self->IntersectPlane((Plane&)other);
	}

	if(m_type == TYPE_AABB && other.GetType() == TYPE_AABB)
	{
		auto self = (AABB*)this;
		return self->IntersectAABB((AABB&)other);
	}

	if (m_type == TYPE_AABB && other.GetType() == TYPE_SIZE)
	{
		auto self = (AABB*)this;
		return self->IntersectPlane((Plane&)other);
	}

	IO::printError(std::basic_string<char>("Error: Collisions not implemented between specified"));

	exit(1);
}

void Collider::Transform(const vec::Vector3& translation)
{ }
