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

	m_infoText = new RenderText(vec::Vector3(5, 250), 1.2f);
}

Camera::Camera(): 
	player(nullptr), rotationAngle(0)
{
	m_infoText = new RenderText(vec::Vector3(5, 250), 1.2f);
}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime)
{
	if (m_showInfo){
		m_info = "Camera Position: " + m_Position.debugString() + "\nVelocity: " + std::to_string(speed) + "Km/s";
	}
}

void Camera::Draw() const
{
	_gluLookAt(eye, m_lookAt, upVec);
}
