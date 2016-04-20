#include "OrbitCamera.h"
#include <Main/Keyboard/Keyboard.h>


OrbitCamera::OrbitCamera()
	: Camera(), m_angle(0), m_speed(0), m_distance(0)
{
	m_focus = Planet();
}

OrbitCamera::OrbitCamera(Planet& _Focus, float distance)
	: Camera()
{
	m_distance = distance;
	m_focus = _Focus;
	m_angle = 0;
	m_speed = 20;
	m_Position = vec::Vector3(0, 0, m_distance);
	eye = m_Position;
	m_lookAt = m_focus.getPositionVec();
	upVec = vec::Vector3::up();
}

OrbitCamera::~OrbitCamera()
{ }

void OrbitCamera::Update(float deltaTime)
{
	m_angle = MathHelper::Clampf(m_angle, -360, 360);
	if(Keyboard::getKeyPressed(KEY_D))
	{
		m_angle += deltaTime * m_speed;
		isMoving = true;
	}
	if(Keyboard::getKeyPressed(KEY_A))
	{
		m_angle -= deltaTime * m_speed;
		isMoving = true; 
	}
	move();
	Camera::Update(deltaTime);
}

void OrbitCamera::Draw() const
{
	Camera::Draw();
}

void OrbitCamera::move()
{
	if (isMoving)
	{
		m_Position.x = sin(MathHelper::ToRadians(m_angle));
		m_Position.z = cos(MathHelper::ToRadians(m_angle));
		m_Position *= m_distance;
		// m_Position.y += 25;
		eye = m_Position;
		m_lookAt = m_focus.getPositionVec();
		upVec = vec::Vector3::up();
	}
}
