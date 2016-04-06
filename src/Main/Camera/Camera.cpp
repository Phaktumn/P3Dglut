#include "Camera.h"

Camera::Camera(Player& player): rotationAngle(0)
{
	this->player = &player;
	this->lookAt = vec::Vector3::zero();
	this->eye = vec::Vector3::zero();
	this->upVec = vec::Vector3::up();
	this->m_Position = vec::Vector3(0, 0, 0);
}

Camera::Camera(vec::Vector3& position, float rotationAngle)
	: player(nullptr)
{

}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime)
{

}

void Camera::Draw() const
{
	gluLookAt(eye.x, eye.y, eye.z,
		lookAt.x, lookAt.y, lookAt.z,
		upVec.x, upVec.y, upVec.z);
}
