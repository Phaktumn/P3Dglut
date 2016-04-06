#include "Planet.h"
#include "SolarSystem.h"
#include "Moon.h"

Planet::Planet(std::string& modelPath, std::string& name, 
	float orbitDuration, float rotatioDuration, vec::Vector3& position, float scale) :
	m_planet_object_(new PhysicsObject(vec::Vector3(5.0, 0.0, -10.0), 10000.0f)),
	m_Sphere(new Object(const_cast<char*>(modelPath.c_str()))), list(0), m_orbit_distance(abs(position.z)),
	m_rotation(0)
{
	this->m_Position = position;
	this->m_Orbit_Duration = orbitDuration;
	this->m_Rotation_Duration = rotatioDuration;
	m_orbit_Angle = 0;
	m_scale = scale;
}

Planet::~Planet()
{
	for (size_t i = 0; i < moons.size(); i++){
		delete(moons[i]);
	}
	delete m_planet_object_;
	delete m_Sphere;
}

void Planet::Load() const
{
	m_Sphere->loadModel();
}

void Planet::Simulate(float deltaTime)
{
	m_orbit_Angle += m_Orbit_Duration;
	if(m_orbit_Angle >= 360) {
		m_orbit_Angle -= 360;
	}
	float radians = MathHelper::ToRadians(m_orbit_Angle);
	m_Position.x = cos(radians) * m_orbit_distance;
	m_Position.z = sin(radians) * m_orbit_distance;

	for (size_t i = 0; i < moons.size(); i++)
	{
		moons[i]->Update(deltaTime);
	}
}

void Planet::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	glScalef(m_scale, m_scale, m_scale);
	glCallList(SolarSystem::m_list + 1);
	glPopMatrix();

	for (size_t i = 0; i < moons.size(); i++) {
		moons[i]->Draw();
	}
}

void Planet::addMoon(float distanceToPlantet, float radius)
{
	moons.push_back(new Moon(*this, distanceToPlantet, radius, 30));
	moons[m_moon_index]->Load();
	m_moon_index++;
}

void Planet::renderOrbit()
{
	glBegin(GL_LINE_STRIP);
	for (float i = 0.0f; i < 6.28318530375f; i+=0.05f){
		glVertex3f(sin(i) * m_orbit_distance, m_Position.y, cos(i) * m_orbit_distance);
	}
	glVertex3f(m_orbit_distance, m_Position.y , m_orbit_distance);
	glEnd();

	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	for (size_t i = 0; i < moons.size(); i++){
		moons[i]->renderOrbit();
	}
	glPopMatrix();
}
