#include "Moon.h"
#include <gl/freeglut.h>
#include "src/Main/Planets/SolarSystem.h"

Moon::Moon(Planet& planet,float distanceToPLanet) 
	: planet_(planet)
{
	this->m_distance_to_planet = distanceToPLanet;
}

Moon::~Moon()
{

}

void Moon::Update(float deltaTime)
{
	this->m_position = planet_.getPositionVec() 
		+ m_distance_to_planet;
}

void Moon::Draw() const
{
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(1, 1, 1);
	//m_Sphere->renderModel();
	glCallList(SolarSystem::m_list + 1);
	glPopMatrix();
}
