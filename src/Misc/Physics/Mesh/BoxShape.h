#pragma once
#include "../../../Vars/Quaternion/Quaternion.h"

class BoxShape
{
public:
	BoxShape();
	explicit BoxShape(float mass);
	~BoxShape();

	float width;
	float height;
	float depth;
	float mass;
	Quaternion momentOfInertia;

	void calculateBoxInertia();
	void inverseMassCalc();
	void computeAuxiliary();
	float getInverseMass() const;

private:
	float inverseMass;
};

inline BoxShape::BoxShape(): 
	width(0), height(0), depth(0), mass(0), inverseMass(0)
{
}

inline BoxShape::BoxShape(float mass): width(0), height(0), depth(0), inverseMass(0)
{
	this->mass = mass;
}

inline BoxShape::~BoxShape()
{
}



inline void BoxShape::calculateBoxInertia()
{
	auto m = this->mass;
	auto w = this->width;
	auto h = this->height;
	auto d = this->depth;
	inverseMassCalc();
	this->momentOfInertia = Quaternion(m / 12 * (w*w + d*d),
		m / 12 * (d*d + h*h),m / 12 * (w*w + h*h), 0);
}

inline void BoxShape::inverseMassCalc()
{
	inverseMass = 1/mass;
}

inline float BoxShape::getInverseMass() const
{ return inverseMass; }
