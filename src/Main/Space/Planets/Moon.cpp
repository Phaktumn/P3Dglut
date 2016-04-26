#include "Moon.h"
#include "SolarSystem.h"
#include <Main/FreeGlutWrap.h>

Moon::Moon(const string& texturePath, const string& name, float orbitDuration, float rotatioDuration, float eccentricity, const Vector3& pos, float scale, float orbitInclination, float planetInclination, Planet& planet, float distanceToPLanet)
	: UniverseObject(texturePath, name, orbitDuration, rotatioDuration, eccentricity, pos, scale, orbitInclination, planetInclination), planet_(planet)
{
	this->m_distance_to_planet = distanceToPLanet;
}

Moon::~Moon()
{
	delete this;
}

void Moon::load()
{
	m_Position = m_Position + m_distance_to_planet;
	m_Aphelion = m_distance_to_planet;
	UniverseObject::load();
}

void Moon::simulate(float deltaTime)
{
	m_Position.x = planet_.getPositionVec().x;
	m_Position.z = planet_.getPositionVec().z;
	UniverseObject::simulate(deltaTime);
}

void Moon::draw()
{
	UniverseObject::draw();
}

void Moon::renderOrbit() const
{
	glPushMatrix();
	_glTranslate(Vector3(planet_.getPositionVec()));
	UniverseObject::renderOrbit();
	glPopMatrix();
}
