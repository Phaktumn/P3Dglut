#pragma once
#include "Camera.h"

class StaticCamera :
	public Camera
{
public:
	StaticCamera(vec::Vector3& position, float rotationAngle);
	~StaticCamera();

	vec::Vector3 m_Orientation;

	void Update(float deltaTime) override;
	void Draw() const override;

	void rotate(float angle);

	void setLookAt(vec::Vector3& lookAt){
		m_lookAt = lookAt;
	}
};

