#pragma once
#include "../../Vars/vec3f.h"

class IntersectData
{
public:
	IntersectData(const bool doesIntersect, const vec::Vector3& direction) : 
		doesIntersect(doesIntersect),
		direction(direction) {}

	bool GetDoesIntersect() const { return doesIntersect; }
	float GetDistance() const { return direction.length(); }
	const vec::Vector3& GetDirection() const { return direction; }
private:
	/** Whether or not the objects are intersecting */
	const bool  doesIntersect;
	/** The collision normal, with length set to distance. */
	const vec::Vector3 direction;
};
