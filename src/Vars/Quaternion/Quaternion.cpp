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

void Quaternion::normalize()
{
	float d = w * w + x * x + y * y + z * z;

	if(d == 0)
	{
		w = 1;
		return;
	}
	d = float(1.0) / sqrt(d);
	w *= d;
	x *= d;
	y *= d;
	z *= d;
}

void Quaternion::operator*=(const Quaternion& multiplier)
{
	Quaternion q = *this;
	w = q.w * multiplier.w - q.x * multiplier.x - q.y * multiplier.y - q.z * multiplier.z;
	x = q.w * multiplier.x + q.x * multiplier.w + q.y * multiplier.z - q.z * multiplier.y;
	y = q.w * multiplier.y + q.y * multiplier.w + q.z * multiplier.x - q.x * multiplier.z;
	z = q.w * multiplier.z + q.z * multiplier.w + q.x * multiplier.y - q.y * multiplier.x;
}

void Quaternion::rotateByVector(const vec::Vector3& vec)
{
	Quaternion q(vec.x * scale, vec.y * scale, vec.z * scale, 0);
	(*this) *= q;
}

void Quaternion::addScaledVector(const vec::Vector3& vec, float scale)
{
	Quaternion q(vec.x * scale, vec.y * scale, vec.z * scale, 0);
	q *= *this;
	w += q.w * float(0.5);
	x += q.x * float(0.5);
	y += q.y * float(0.5);
	z += q.z * float(0.5);
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
