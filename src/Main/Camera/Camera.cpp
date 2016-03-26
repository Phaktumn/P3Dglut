#include "Camera.h"

Camera::Camera(Player& player): rotationAngle(0)
{
	this->player = &player;
	this->lookAt = vec::Vector3::zero();
	this->eye = vec::Vector3::zero();
	this->upVec = vec::Vector3::up();
}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime)
{
	//this is the center!
	this->rotationAngle = player->getRigidBody().angle;
	eye = player->getRigidBody().position;
	eye += vec::Vector3(-sin(this->rotationAngle) * 5, 2, cos(rotationAngle) * 5);	
	lookAt = player->getRigidBody().position + player->getRigidBody().orientation;
	upVec = vec::Vector3(1.0, 1.0, 1.0) * player->getRigidBody().orientation;
}

void Camera::Draw() const
{
	gluLookAt(eye.x, eye.y, eye.z,
		lookAt.x, lookAt.y, lookAt.z,
		upVec.x, upVec.y, upVec.z);
}
