#pragma once
#include <string>

namespace vec{
	class Vector3;
}

class Quaternion
{
public:
	//Public Fields
	float x;
	float y;
	float z;
	float w;

	float scale = 1;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(vec::Vector3& vec, float w);
	~Quaternion();

	std::string debug = "{x: " + std::to_string(x) + 
						" y: " + std::to_string(y) +
						" z: " + std::to_string(z) +
		                " w: " + std::to_string(w) + "}";
	void normalize();
	void operator*=(const Quaternion &multiplier);

	void rotateByVector(const vec::Vector3 &vec);
	void addScaledVector(const vec::Vector3 &vec, float scale);

	static Quaternion Identity() { return identity_quaternion_; }
	static Quaternion CreateFromAxisAngle(vec::Vector3 axis, float angle);
	static Quaternion Add(Quaternion q1, Quaternion q2);

private:
	static Quaternion identity_quaternion_;
};

