#include "Moon.h"
#include <gl/freeglut.h>
#include "SolarSystem.h"

Moon::Moon(Planet& planet,float distanceToPLanet, float scale) 
	: planet_(planet)
{
	this->m_distance_to_planet = distanceToPLanet;
	m_planet_scale = scale;
	m_northPoleNormal = vec::Vector3::up();
}

Moon::~Moon()
{

}

void Moon::Load()
{
	this->m_position = planet_.getPositionVec() 
		+ m_distance_to_planet;
}

void Moon::Update(float deltaTime)
{
	this->m_position = planet_.getPositionVec() 
		+ m_distance_to_planet;

	//Rotate 
	m_rotation_angle += 0.01f;
	if (m_rotation_angle >= 360) m_rotation_angle -= m_rotation_angle;
}

void Moon::Draw() const
{
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_rotation_angle, m_northPoleNormal.x, m_northPoleNormal.y, m_northPoleNormal.z);
	glScalef(m_planet_scale, m_planet_scale, m_planet_scale);
	//m_Sphere->renderModel();
	glCallList(SolarSystem::m_list + 1);
	glPopMatrix();
}
