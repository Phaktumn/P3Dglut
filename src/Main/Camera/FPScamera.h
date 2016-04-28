#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#pragma once
#include "Camera.h"
#include <Main/Globals.h>
#include <Misc/RenderText.h>

using namespace vec;
 
class EulerAngle;

class FPScamera
	: public Camera
{
public:
	FPScamera(): angle(nullptr)
	{ }
	
	explicit FPScamera(const Vector3& pos)
		: Camera(pos), angle(nullptr)
	{
		currentMousePosition = Vector3(glutGet(GLUT_WINDOW_WIDTH) / 2,
			glutGet(GLUT_WINDOW_HEIGHT) / 2,
			0);
		viewPortCenter = currentMousePosition;
		rightVector = Vector3::right();
		upVec = Vector3::up();
		forwardVec = Vector3(0, 0, 1);
	}

	~FPScamera() override;
	void Update(float deltaTime) override;
	void Draw() const override;

private:
	EulerAngle* angle;

	Vector3 viewPortCenter;

	Vector3 currentMousePosition;
	Vector3 prevMousePos;

	Vector3 diff;
	void computeMouse();

	float pitch = 0;
	float yaw = 0;
	float sensitivity = .06f;
};
#endif

