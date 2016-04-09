#include "StaticCamera.h"
#include "../Keyboard/Keyboard.h"

StaticCamera::StaticCamera(vec::Vector3& position, float):
	Camera(position)
{
	m_lookAt = vec::Vector3::zero();
	eye = position;
	upVec = vec::Vector3::up();
	m_Orientation = vec::Vector3::zero();
	rotationAngle = 0.1;
	this->m_Position = vec::Vector3(0, 0, 0);
	m_Position.y = 15;
}

StaticCamera::~StaticCamera()
{

}

void StaticCamera::Update(float deltaTime)
{
	if(Keyboard::getKeyPressed(KEY_D)) {
		rotate(0.005f);
	}
	if (Keyboard::getKeyPressed(KEY_W)) {
		m_Position += vec::Vector3(1, 0, 1) * m_Orientation;
	}
	if (Keyboard::getKeyPressed(KEY_A)) {
		rotate(-0.005f);
	}
	eye = m_Position;
	eye += vec::Vector3(-sin(this->rotationAngle), 0, cos(rotationAngle));
	m_lookAt = m_Position + m_Orientation;
	upVec = vec::Vector3::up();
	Camera::Update(deltaTime);
}



void StaticCamera::Draw() const
{
	Camera::Draw();
}

void StaticCamera::rotate(float angle) 
{
	this->rotationAngle += angle;
	m_Orientation.x = sin(rotationAngle);
	m_Orientation.y = 0;
	m_Orientation.z = -cos(rotationAngle);
}
