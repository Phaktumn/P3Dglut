#include "Planet.h"

Planet::Planet(std::string& modelPath, std::string& name, 
	float orbitDuration, float rotatioDuration, vec::Vector3& position, float scale) :
	m_planet_object_(PhysicsObject(vec::Vector3(5.0, 0.0, -10.0), 10000.0f)),
	m_Sphere(Object(const_cast<char*>(modelPath.c_str()))), m_orbit_distance(abs(position.z)),
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

}

void Planet::Load()
{
	m_Sphere.loadModel();
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
}

void Planet::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	glScalef(m_scale, m_scale, m_scale);
	m_Sphere.renderModel();
	glPopMatrix();
}
