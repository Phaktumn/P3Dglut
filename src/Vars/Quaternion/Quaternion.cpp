#include "Quaternion.h"
#include "../vec3f.h"

Quaternion Quaternion::identity_quaternion_ = Quaternion(0, 0, 0, 1);

Quaternion::Quaternion(): x(0), y(0), z(0), w(0) { }

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(vec::Vector3& vec, float w)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}

Quaternion::~Quaternion()
{
}

Quaternion Quaternion::CreateFromAxisAngle(vec::Vector3 axis, float angle)
{
	auto half = angle * 0.5f;
	auto sin = float(std::sin(half));
	auto cos = float(std::cos(half));
	return Quaternion(axis.x * sin, axis.y * sin, axis.z * sin, cos);
}

Quaternion Quaternion::Add(Quaternion q1, Quaternion q2)
{
	Quaternion result_quaternion;
	result_quaternion.x = q1.x + q2.x;
	result_quaternion.y = q1.y + q2.y;
	result_quaternion.z = q1.z + q2.z;
	return result_quaternion;
}
