#include "OrbitCamera.h"
#include <Main/Keyboard/Keyboard.h>


OrbitCamera::OrbitCamera()
	: Camera(), m_distance(0), m_angle(0), m_speed(0)
{
	m_focus = Planet();
}

OrbitCamera::OrbitCamera(Planet& _Focus, vec::Vector3& _Position)
	: Camera(_Position)
{
	m_focus = _Focus;
	m_distance = 150;
	m_angle = 0;
	m_speed = 20;
}

OrbitCamera::~OrbitCamera()
{ }

void OrbitCamera::Update(float deltaTime)
{
	m_angle = MathHelper::Clampf(m_angle, 0, 360);
	if(Keyboard::getKeyPressed(KEY_D))
	{
		rotate(MathHelper::ToRadians(m_angle), deltaTime);
	}
	if(Keyboard::getKeyPressed(KEY_A))
	{
		rotate(MathHelper::ToRadians(m_angle), -deltaTime);
	}
}

void OrbitCamera::Draw() const
{
	Camera::Draw();
}

void OrbitCamera::rotate(float _radians, float _deltaTime)
{
	m_angle += _deltaTime * m_speed;
	m_Position.x = sin(_radians) * m_distance;
	m_Position.z = cos(_radians) * m_distance;
	eye = m_Position;
	m_lookAt = m_focus.getPositionVec();
	upVec = vec::Vector3::up();
}
