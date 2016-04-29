#pragma once
#include "Camera.h"
#include <Vars/EulerAngle.h>

class SimpleCamera :
	public Camera
{
public:
	SimpleCamera(const vec::Vector3& position, float rotationAngle, const bool _orbit);
	~SimpleCamera();

	vec::Vector3 m_Orientation;

	void Update(float deltaTime) override;
	void Draw() const override;

	void rotate(float angle);

	void setLookAt(vec::Vector3& lookAt){
		m_lookAt = lookAt;
	}

private:
	EulerAngle angle;
	float rotateUp = 0;
	float distance = 500;
	float m_speed;
};

