#include "SolarSystem.h"
#include <list>

SolarSystem::SolarSystem(const int planetCount)
{
	m_list = glGenLists(planetCount);
	//Add Sun
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"), 
		std::string("Earth"), 0.09f, 0.6f, vec::Vector3(0, 0, 10), 1.0));
	
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Jupiter"), 0.05f, 0.6f, vec::Vector3(0, 0, 30), 2.0));
	
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Uranus"), 0.03f, 0.6f, vec::Vector3(0, 0, 45), 1.8));
	
	m_Planets.push_back(Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Mars"), 0.1f, 0.6f, vec::Vector3(0, 0, 15), 0.85));
}

SolarSystem::~SolarSystem()
{

}


void SolarSystem::Load()
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i].Load();
	}
}

void SolarSystem::Simulate(float deltaTime)
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		m_Planets[i].Simulate(deltaTime);
	}
}

void SolarSystem::Draw()
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i].Draw();
	}
}
