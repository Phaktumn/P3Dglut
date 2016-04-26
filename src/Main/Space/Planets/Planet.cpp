#include "Planet.h"
#include <Main/Space/Rings.h>
#include <Main/FreeGlutWrap.h>
#include <Main/Globals.h>

Planet::Planet(const string& texturePath, const  string& name,
	float orbitDuration, float rotatioDuration, float eccentricity, 
	const Vector3& position, float scale, float orbitInclination, float planetInclnation) : 
	UniverseObject(texturePath, name, orbitDuration, rotatioDuration, eccentricity 
		,position, scale, orbitInclination, planetInclnation),  ring(nullptr)
{
}

Planet::~Planet()
{
	//Delete all moons
	for (size_t i = 0; i < moons.size(); i++){
		delete moons[i];
	}
	delete ring;
}

void Planet::load()
{
	UniverseObject::load();
}

void Planet::simulate(float deltaTime)
{
	//Dont Update Moons if moon list is equals to zero
	if (m_moon_index == 0) UniverseObject::simulate(deltaTime);
	for (size_t i = 0; i < moons.size(); i++) {
		moons[i]->simulate(deltaTime);
	}
	UniverseObject::simulate(deltaTime);
}

void Planet::draw()
{
	if(ring != nullptr)
		ring->draw(*this);

	//Dont Draw Moons if moon list size is equal to zero
	if (m_moon_index == 0) UniverseObject::draw();
	//Else draw this planet moons
	for (size_t i = 0; i < moons.size(); i++) {
		glPushMatrix();
		_glTranslate(m_Position);
		moons[i]->draw();
		glPopMatrix();
	}

	UniverseObject::draw();
}

void Planet::addMoon(float distanceToPlantet, float radius)
{
	GLUquadric* aux_Sphere = gluNewQuadric();
	gluQuadricNormals(aux_Sphere, GLU_SMOOTH);
	gluQuadricDrawStyle(aux_Sphere, GLU_FILL);
	gluQuadricTexture(aux_Sphere, GLU_TRUE);
	if (distanceToPlantet < m_scale) distanceToPlantet = m_scale + 10;
	moons.push_back(new Moon("Textures/moon.bmp", "Moon", 27.3f, 29.5f, 0.0549f, m_Position,
		radius, 32.0f, 6.687f, *this, distanceToPlantet));
	moons[m_moon_index]->setSphere(aux_Sphere);
	moons[m_moon_index]->load();
	m_moon_index++;
}

void Planet::renderOrbit() const
{
	glDisable(GL_TEXTURE_2D);
	//No moons just return
	if (m_moon_index == 0) UniverseObject::renderOrbit();
	for (size_t i = 0; i < moons.size(); i++) { moons[i]->renderOrbit(); }
	glEnable(GL_TEXTURE_2D);
	UniverseObject::renderOrbit();
}

string& Planet::objectSettigs()
{
	m_planetSettings = "Name: "                  + m_Name;
	m_planetSettings += "\n Position: "          + getPosition();
	m_planetSettings += "\n Distance to Sun: "   + to_string(m_KeplerOrbitDistance)              + "Mill km";
	m_planetSettings += "\n Rotation: "          + to_string(m_rotation);
	m_planetSettings += "\n Orbit Angle: "       + to_string(m_orbit_Angle);
	m_planetSettings += "\n Orbit Duration: "    + to_string(int(m_Orbit_Duration))              + " Earth Days";
	if(m_Rotation_Duration < 1.0f) 
		m_planetSettings +=  "\n Day Duration: " + to_string(double(m_Rotation_Duration * 24))   + " Earth Hours";
	else m_planetSettings += "\n Day Duration: " + to_string(int(m_Rotation_Duration))           + " Earth Days";
	m_planetSettings += "\n Days Elapsed on "    + m_Name + ": " + to_string(m_days_elapsed)     + " Days";
	m_planetSettings += "\n Years Elapsed on "   + m_Name + ": " + to_string(m_years_elapsed)    + " Years";
	
	return {m_planetSettings};
}

void Planet::addRings(float innerRadius, float outterRadius)
{
	ring = new Ring(innerRadius, outterRadius, 50, 1);
	ring->load();
	ring->attachToPlanet(*this);
}
