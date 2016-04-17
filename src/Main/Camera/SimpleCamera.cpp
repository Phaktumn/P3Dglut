#include "../Keyboard/Keyboard.h"
#include "SimpleCamera.h"

SimpleCamera::SimpleCamera(const vec::Vector3& position, float):
	Camera(position)
{
	m_lookAt = vec::Vector3::zero();
	eye = position;
	upVec = vec::Vector3::up();
	m_Orientation = vec::Vector3::zero();
	rotationAngle = 0.1;
	this->m_Position = position;
	m_speed = 50;
}

SimpleCamera::~SimpleCamera()
{

}

void SimpleCamera::Update(float deltaTime)
{
	if(Keyboard::getKeyPressed(KEY_D)) {
		rotate(deltaTime);
	}
	if (Keyboard::getKeyPressed(KEY_W)) {
		m_Position += vec::Vector3(1, 0, 1) *
			m_Orientation * m_speed * deltaTime;
	}
	if (Keyboard::getKeyPressed(KEY_A)) {
		rotate(-deltaTime);
	}
	if(Keyboard::getKeyPressed(KEY_Q)) {
		m_Position -= upVec * m_speed * deltaTime;
	}
	if (Keyboard::getKeyPressed(KEY_E)) {
		m_Position += upVec * m_speed * deltaTime;
	}
	eye = m_Position;
	eye += vec::Vector3(-sin(this->rotationAngle), 0, cos(rotationAngle));
	m_lookAt = m_Position + m_Orientation;
	upVec = vec::Vector3::up();
	Camera::Update(deltaTime);
}



void SimpleCamera::Draw() const
{
	Camera::Draw();
}

void SimpleCamera::rotate(float angle) 
{
	this->rotationAngle += angle;
	m_Orientation.x = sin(rotationAngle);
	m_Orientation.y = 0;
	m_Orientation.z = -cos(rotationAngle);
}
