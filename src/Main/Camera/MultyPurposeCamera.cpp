#include "MultiPurposeCamera.h"



MultiPurposeCamera::MultiPurposeCamera(Player& player)
	: Camera(player)
{

}


MultiPurposeCamera::~MultiPurposeCamera()
{
}

void MultiPurposeCamera::Update(float deltaTime)
{
	//this is the center!
	if (player != nullptr)
	{
		rotationAngle = player->getRigidBody().angle;
		eye = player->getRigidBody().position;
		eye += vec::Vector3(-sin(this->rotationAngle) * 5, 2, cos(rotationAngle) * 5);
		lookAt = player->getRigidBody().position + player->getRigidBody().orientation;
		upVec = vec::Vector3(1.0, 1.0, 1.0) * player->getRigidBody().orientation;
	}
	Camera::Update(deltaTime);
}

void MultiPurposeCamera::Draw() const
{
	Camera::Draw();
}

