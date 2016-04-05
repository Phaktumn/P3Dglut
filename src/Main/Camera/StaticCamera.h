#pragma once
#include "Camera.h"

class StaticCamera :
	public Camera
{
public:
	StaticCamera(vec::Vector3& position, float rotationAngle);
	~StaticCamera();

	void Update(float deltaTime) override;
	void Draw() const override;
};

