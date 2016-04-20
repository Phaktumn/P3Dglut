#pragma once
#include "Camera.h"
#include <Main/Space/Planets/Planet.h>

class OrbitCamera :
	public Camera
{
public:
	OrbitCamera();
	explicit OrbitCamera(Planet&,float distance);
	~OrbitCamera();
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	void move();
	void rotate(float,float);
	float m_angle;
	float m_speed;
	float m_distance;
	vec::Vector3 aux;
	bool isMoving = false;
	Planet m_focus;
};
