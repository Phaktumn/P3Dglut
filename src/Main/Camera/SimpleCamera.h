#pragma once
#include "Camera.h"

class SimpleCamera :
	public Camera
{
public:
	SimpleCamera(const vec::Vector3& position, float rotationAngle);
	~SimpleCamera();

	vec::Vector3 m_Orientation;

	void Update(float deltaTime) override;
	void Draw() const override;

	void rotate(float angle);

	void setLookAt(vec::Vector3& lookAt){
		m_lookAt = lookAt;
	}

private:
	float m_speed;
};

