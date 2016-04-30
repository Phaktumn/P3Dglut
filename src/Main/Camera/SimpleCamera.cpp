#include "../Keyboard/Keyboard.h"
#include "SimpleCamera.h"

SimpleCamera::SimpleCamera(const Vector3& position, float,const bool _orbit):
	Camera(position,_orbit), m_focus(nullptr)
{
	m_lookAt = Vector3::zero();
	eye = position;
	upVec = Vector3::up();
	rotationAngle = 0.0f;
	m_Position = position;
	m_speed = 50;
}

SimpleCamera::~SimpleCamera()
{

}

void SimpleCamera::Update(float deltaTime)
{
	if(Keyboard::getKeyPressed(KEY_D)) {
		rotate(-m_speed * deltaTime);
	}
	if (Keyboard::getKeyPressed(KEY_W)) {
		rotateUp -= m_speed * deltaTime;
	}
	if (Keyboard::getKeyPressed(KEY_S)) {
		rotateUp += m_speed * deltaTime;
	}
	if (Keyboard::getKeyPressed(KEY_A)) {
		rotate(m_speed * deltaTime);
	}

	if(Keyboard::getKeyPressed(KEY_Q))
	{
		distance -= m_speed * deltaTime;
	}
	if (Keyboard::getKeyPressed(KEY_E))
	{
		distance += m_speed * deltaTime;
	}


	if(m_focus!=nullptr){
		Vector3 focusPos = m_focus->getPositionVec();
		Vector3 eulerRotVec = EulerAngle(rotationAngle, rotateUp, 0).toVector3();
		forwardVec = Vector3::Normalize(focusPos + eulerRotVec);
		eye = focusPos;
		eye += eulerRotVec * distance;
		m_lookAt = focusPos;
		upVec = Vector3::up();
	}
	else
	{
		forwardVec = EulerAngle(rotationAngle, rotateUp, 0).toVector3();
		m_lookAt = Vector3::zero() - forwardVec;
		eye = m_lookAt * distanceSun;
		upVec = Vector3::Normalize(forwardVec - Vector3(0, sin(180), 0));
	}
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
