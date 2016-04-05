#include "StaticCamera.h"

StaticCamera::StaticCamera(vec::Vector3& position, float _rotationAngle):
	Camera(position, _rotationAngle)
{
	lookAt = vec::Vector3::zero();
	eye = position;
	upVec = vec::Vector3::up();
}

StaticCamera::~StaticCamera()
{

}

void StaticCamera::Update(float deltaTime)
{
	Camera::Update(deltaTime);
}

void StaticCamera::Draw() const
{
	Camera::Draw();
}
