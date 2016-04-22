#pragma once
#include "Camera.h"
#include <Vars/EulerAngle.h>

class FPScamera
	: public Camera
{
public:
	FPScamera(): angle(nullptr)
	{ }
	
	explicit FPScamera(const vec::Vector3& pos)
		: Camera(pos), angle(nullptr)
	{
		currentMousePosition = vec::Vector3(glutGet(GLUT_WINDOW_WIDTH) / 2,
			glutGet(GLUT_WINDOW_HEIGHT) / 2,
			0);
		rightVector = vec::Vector3::right();
		upVec = vec::Vector3::up();
		forwardVec = vec::Vector3(0, 0, 1);
	}

	~FPScamera() override;
	void Update(float deltaTime) override;
	void Draw() const override;
private:
	EulerAngle* angle;

	float speed = 10.0f;

	vec::Vector3 viewPortCenter;

	vec::Vector3 currentMousePosition;
	vec::Vector3 prevMousePos;
	vec::Vector3 rightVector;
	vec::Vector3 upVec;
	vec::Vector3 forwardVec;
	float pitch = 0;
	float yaw = 0;
	float sensitivity = .10f;
};
