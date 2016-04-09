#include "Moon.h"
#include <gl/freeglut.h>
#include "SolarSystem.h"

Moon::Moon(Planet& planet,float distanceToPLanet, float scale, float orbitAngle) 
	: planet_(planet)
{
	this->m_distance_to_planet = distanceToPLanet;
	m_planet_scale = scale;
	m_northPoleNormal = vec::Vector3::up();
	m_orbit_angle = orbitAngle;
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
	m_position.y += planet_.getPositionVec().y;
	m_position.z += sin(MathHelper::ToRadians(m_rotation_angle)) * m_distance_to_planet;
}

void Moon::Draw() const
{
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_rotation_angle, 0, 0, -1);
	glScalef(m_planet_scale, m_planet_scale, m_planet_scale);
	glCallList(SolarSystem::m_list + 1);
	glPopMatrix();
}

void Moon::renderOrbit() const
{
	glBegin(GL_LINE_STRIP);
	for (float i = 0.0f; i < 6.28318530375f; i += 3.14 / 180) {
		glVertex3f(sin(i) * m_distance_to_planet, 
			m_position.y, cos(i) * m_distance_to_planet);
	}
	glEnd();
}
