#ifndef EULER_H_
#define EULER_H_

#pragma once
#include "vec3f.h"

using namespace vec;

class EulerAngle
{
public:
	EulerAngle();
	EulerAngle(float ,float ,float);
	explicit EulerAngle(Vector3& yawPitchRoll);
	~EulerAngle();

	Vector3& toVector3() const;
	Vector3& toVector3Inv() const;
	//const Vector3& yawToVec(const float angle_X) const;
	//const Vector3& pitchToVec(const float angle_Y) const;

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

inline Vector3& EulerAngle::toVector3() const
{
	Vector3 vecEuler;
	vecEuler.x = cos(MathHelper::ToRadians(Yaw)) * cos(MathHelper::ToRadians(Pitch));
	vecEuler.y = sin(MathHelper::ToRadians(Pitch));
	vecEuler.z = sin(MathHelper::ToRadians(Yaw)) * cos(MathHelper::ToRadians(Pitch));
	return vecEuler;
}

inline Vector3& EulerAngle::toVector3Inv() const
{
	Vector3 vecEuler;
	vecEuler.x = sinf(Pitch);
	vecEuler.y = sinf(Pitch) * cosf(Yaw);
	vecEuler.z = cosf(Pitch) * cosf(Yaw);
	return vecEuler;
}


#endif
