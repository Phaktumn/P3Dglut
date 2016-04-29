#include "Camera.h"
#include <Main/FreeGlutWrap.h>

Camera::Camera(Player& player)
	: m_infoText(nullptr), rotationAngle(0)
{
	this->player = &player;
	this->m_lookAt = Vector3::zero();
	this->eye = Vector3::zero();
	this->upVec = Vector3::up();
	this->m_Position = Vector3(0, 0, 0);

}

Camera::Camera(const vec::Vector3& position, const bool _orbit)
	: player(nullptr), rotationAngle(0){
	m_infoText = new RenderText(Vector3(5, 250), 1.2f);
	isOrbiting = _orbit;
	m_Position = position;
}

Camera::Camera(): 
	player(nullptr), rotationAngle(0)
{
	m_infoText = new RenderText(Vector3(10, 10), 1.2f);
}

Camera::~Camera()
{ }

void Camera::Update(float deltaTime)
{
	if (m_showInfo){
		m_info = "Camera Position: " + m_Position.debugString() + "\nVelocity: " + std::to_string(speed/Universal_Metric_Scale * 0.001) + "Km/s";
	}
}

void Camera::Draw() const
{
	_gluLookAt(eye, m_lookAt, upVec);
}
