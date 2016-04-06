#include "SolarSystem.h"
#include "../../Misc/Debug/IO.h"
#include "Moon.h"

GLuint SolarSystem::m_list = glGenLists(1);

SolarSystem::SolarSystem()
{
	//Add Sun
	m_Planets.push_back(new Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Sun"), 0.0f, 0.5f, vec::Vector3(0, 0, 0), 15.0f));

	m_Planets.push_back(new Planet(std::string("Modelos3D/Sun.obj"), 
		std::string("DmnBig"), 0.01f, 0.5f, vec::Vector3(0, 0, 150), 3.0));

	m_Planets.push_back(new Planet(std::string("Modelos3D/Sun.obj"), 
		std::string("Earth"), 0.09f, 0.6f, vec::Vector3(0, 0, 20), 1.0));
	
	m_Planets.push_back(new Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Jupiter"), 0.05f, 0.6f, vec::Vector3(0, 0, 85), 4));
	
	m_Planets.push_back(new Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Uranus"), 0.03f, 0.6f, vec::Vector3(0, 0, 100), 4.5));
	
	m_Planets.push_back(new Planet(std::string("Modelos3D/Sun.obj"),
		std::string("Mars"), 0.08f, 0.6f, vec::Vector3(0, 0, 25), 0.85));
}

SolarSystem::~SolarSystem()
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		delete m_Planets[i];
	}
}

void SolarSystem::Load()
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Load();
	}

	m_Planets[1]->addMoon(10, 0.5f);

	glNewList(m_list + 1, GL_COMPILE);
		m_Planets[0]->getObject().renderModel();
	glEndList();
}

void SolarSystem::Simulate(float deltaTime)
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		m_Planets[i]->Simulate(deltaTime);
	}
}

void SolarSystem::Draw() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Draw();
	}
}

void SolarSystem::renderOrbits()
{
	glDisable(GL_LIGHTING);
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->renderOrbit();
	}
	glEnable(GL_LIGHTING);
}
