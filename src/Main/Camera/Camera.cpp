#include "Camera.h"
#include <Main/FreeGlutWrap.h>

Camera::Camera(Player& player): rotationAngle(0)
{
	this->player = &player;
	this->m_lookAt = Vector3::zero();
	this->eye = Vector3::zero();
	this->upVec = Vector3::up();
	this->m_Position = Vector3(0, 0, 0);
}

Camera::Camera(const Vector3& position)
	: player(nullptr), rotationAngle(0)
{

}

Camera::Camera(): 
	player(nullptr), rotationAngle(0)
{

}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime)
{

}

void Camera::Draw() const
{
	_gluLookAt(eye, m_lookAt, upVec);
}
