#pragma once
#include "Camera.h"
#include <Vars/EulerAngle.h>
#include <Main/Space/Planets/Planet.h>

class SimpleCamera :
	public Camera
{
public:
	SimpleCamera(const Vector3& position, float rotationAngle, const bool _orbit);
	~SimpleCamera();

	Vector3 m_Orientation;

	void Update(float deltaTime) override;
	void Draw() const override;

	void rotate(float angle);

	void setLookAt(Vector3& lookAt) {
		m_lookAt = lookAt;
	}

	void setFocus(Planet* _focus_planet){
		this->m_focus = _focus_planet;
	}

private:

	Planet* m_focus;

	EulerAngle angle;
	float rotateUp = 0;
	float distance = 25;
	float m_speed;
};

