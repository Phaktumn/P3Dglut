#ifndef COLLIDER_INCLUDED_H
#define COLLIDER_INCLUDED_H

#pragma once
#include "../../Main/ReferenceCounter.h"
#include "../../Vars/vec3f.h"
#include "../../Misc/Physics/IntersectData.h"

class Collider : public ReferenceCounter 
{
public:
	enum Type
	{
		TYPE_SPHERE,
		TYPE_AABB,
		TYPE_SIZE
	};

	explicit Collider(int Type) : ReferenceCounter(), m_type(Type){}
	IntersectData Intersect(const Collider& other) const;
	virtual void Tranform(const vec::Vector3& tranlation){}
	virtual vec::Vector3 GetCenter() const { return vec::Vector3(0, 0, 0); }

	/** Basic Getter */
	int GetType() const { return m_type; }

private:
	int m_type;
};

#endif


