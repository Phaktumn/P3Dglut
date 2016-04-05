#include "SolarSystem.h"
#include "../../Misc/Debug/IO.h"

SolarSystem::SolarSystem()
{
	m_list = glGenLists(1);

	//Add Sun
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Sun"), 0.0f, 0.5f, vec::Vector3(0, 0, 0), 15.0f));

	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"), 
		std::string("Sun"), 0.01f, 0.5f, vec::Vector3(0, 0, 150), 3.0));

	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"), 
		std::string("Earth"), 0.09f, 0.6f, vec::Vector3(0, 0, 20), 1.0));
	
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Jupiter"), 0.05f, 0.6f, vec::Vector3(0, 0, 85), 4));
	
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Uranus"), 0.03f, 0.6f, vec::Vector3(0, 0, 100), 4.5));
	
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Mars"), 0.08f, 0.6f, vec::Vector3(0, 0, 25), 0.85));
}

SolarSystem::~SolarSystem()
{

}


void SolarSystem::Load()
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i].Load();
	}

	glNewList(1, GL_COMPILE);
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i].Draw();
	}
	glEndList();
}

void SolarSystem::Simulate(float deltaTime)
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		m_Planets[i].Simulate(deltaTime);
	}
}

void SolarSystem::Draw() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i].Draw();
	}
	//glCallList(m_list + 1);
}
