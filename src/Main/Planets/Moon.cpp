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
	//Rotate 
	m_rotation_angle += 0.1f;
	if (m_rotation_angle >= 360) 
		m_rotation_angle -= m_rotation_angle;

	m_position = planet_.getPositionVec();
	m_position.x += cos(MathHelper::ToRadians(m_rotation_angle)) * m_distance_to_planet;
	//ReWrite This ples!
	m_position.y += (sin(MathHelper::ToRadians(m_rotation_angle)) +
		cos(MathHelper::ToRadians(m_rotation_angle))) * m_distance_to_planet;
	m_position.z += sin(MathHelper::ToRadians(m_rotation_angle)) * m_distance_to_planet;
}

void Moon::Draw() const
{
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(m_planet_scale, m_planet_scale, m_planet_scale);
	glCallList(SolarSystem::m_list + 1);
	glPopMatrix();
}
