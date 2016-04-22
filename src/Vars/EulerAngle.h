#pragma once
#include "vec3f.h"
#include <vector>

class EulerAngle
{
public:
	EulerAngle();
	EulerAngle(float ,float ,float);
	explicit EulerAngle(vec::Vector3& yawPitchRoll);
	~EulerAngle();

	vec::Vector3& toVector3() const;

private:
	float Pitch;
	float Yaw;
	float Roll;
};

inline EulerAngle::EulerAngle()
	: Pitch(0), Yaw(0), Roll(0) { }
inline EulerAngle::~EulerAngle() { }


inline EulerAngle::EulerAngle(float _Yaw,float _Pitch, float _Roll)
{
	Pitch = _Pitch;
	Yaw = _Yaw;
	Roll = _Roll;
}

inline vec::Vector3& EulerAngle::toVector3() const
{
	vec::Vector3 vecEuler;
	vecEuler.x = sin(Yaw);
	vecEuler.y = -(sin(Pitch)*cos(Yaw));
	vecEuler.z = -(cos(Pitch)*cos(Yaw));
	return vecEuler;
}
