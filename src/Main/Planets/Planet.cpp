#include "Planet.h"
#include "SolarSystem.h"

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
	//m_Sphere->renderModel();
	glCallList(SolarSystem::m_list + 1);
	glPopMatrix();

	for (size_t i = 0; i < moons.size(); i++) {
		moons[i]->Draw();
	}
}

void Planet::addMoon(Moon* moon)
{
	moons.push_back(moon);
	moons[m_moon_index]->m_position.x = 
		this->m_Position.x + moons[m_moon_index]->m_distance_to_planet;
	moons[m_moon_index]->m_position.y =
		this->m_Position.y + moons[m_moon_index]->m_distance_to_planet;
	moons[m_moon_index]->m_position.z = this->m_Position.z;
	m_moon_index++;
}
