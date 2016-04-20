#include "Camera.h"

Camera::Camera(Player& player): rotationAngle(0)
{
	this->player = &player;
	this->m_lookAt = vec::Vector3::zero();
	this->eye = vec::Vector3::zero();
	this->upVec = vec::Vector3::up();
	this->m_Position = vec::Vector3(0, 0, 0);
}

Camera::Camera()
	: player(nullptr), rotationAngle(0)
{
}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime)
{
	m_Forward = vec::Vector3::Normalize(m_lookAt - m_Position);
	//m_Right = vec::Vector3::Cross(vec::Vector3::up(), m_Forward).Normalized();
	//upVec = vec::Vector3::Cross(m_Forward, m_Right).Normalized();
}

void Camera::Draw() const
{
	gluLookAt(
		eye.x     , eye.y     , eye.z,
		m_lookAt.x, m_lookAt.y, m_lookAt.z,
		upVec.x   , upVec.y   , upVec.z);
}
