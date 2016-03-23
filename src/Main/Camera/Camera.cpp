#include "Camera.h"

Camera::Camera(): rotationAngle(0)
{
}

Camera::Camera(Player* player): rotationAngle(0)
{
	this->player = player;
	this->lookAt = vec::Vector3::zero();
	this->eye = vec::Vector3::zero();
	this->upVec = vec::Vector3::up();
}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime, float angle)
{
	//this is the center!
	this->rotationAngle = angle;
	eye = player->getTranform()->getPosition();
	eye += vec::Vector3(-sin(this->rotationAngle) * 5, 2, cos(rotationAngle) * 5);
	lookAt = player->getTranform()->getPosition() + player->getTranform()->getRotation();
	upVec = vec::Vector3(1.0, 1.0, 1.0) * player->getTranform()->getRotation();
}

void Camera::Draw() const
{
	gluLookAt(eye.x, eye.y, eye.z,
		lookAt.x, lookAt.y, lookAt.z,
		upVec.x, upVec.y, upVec.z);
}
