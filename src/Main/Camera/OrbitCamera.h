#pragma once
#include "Camera.h"
#include <Main/Space/Planets/Planet.h>

class OrbitCamera :
	public Camera
{
public:
	OrbitCamera();
	explicit OrbitCamera(Planet&,vec::Vector3&);
	~OrbitCamera();
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	void rotate(float,float);
	float m_distance;
	float m_angle;
	float m_speed;

	Planet m_focus;
};
