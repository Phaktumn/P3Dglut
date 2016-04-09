#include "SolarSystem.h"
#include "../../Misc/Debug/IO.h"
#include <Misc/RenderText.h>

GLuint SolarSystem::m_list = glGenLists(1);

SolarSystem::SolarSystem()
{
	m_Planets.push_back(new Planet(std::string("Textures/sun.bmp"),
		std::string("Sun"), 0.01f, 0.0f, vec::Vector3(0, 0, 0), 50));

	m_Planets.push_back(new Planet("Textures/mercury.bmp", 
		"Mercurio", 88.0f, 0.1f, vec::Vector3(0, 0, 70), 0.3f));

	m_Planets.push_back(new Planet(std::string("Textures/earth.bmp"), 
		"Venus", 224.0f, 0.1f, vec::Vector3(0, 0, 108), 0.4f));
	
	m_Planets.push_back(new Planet(std::string("Textures/earth.bmp"),
		"Earth", 365.0f, 1.0f, vec::Vector3(0, 0, 150), 1.0f));
	
	m_Planets.push_back(new Planet(std::string("Textures/mars.bmp"),
		"Mars", 687.0f, 0.1f, vec::Vector3(0, 0, 228), 1.0f));

	m_Planets.push_back(new Planet(std::string("Textures/jupiter.bmp"),
		"Jupiter", 4332.0f, 0.1f, vec::Vector3(0, 0, 772), 11.5f));
	
	m_Planets.push_back(new Planet(std::string("Textures/saturn.bmp"),
		"Saturn", 10760.0f, 0.6f, vec::Vector3(0, 0, 1443), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/uranus.bmp"),
		"Uranus", 30700.0f, 0.6f, vec::Vector3(0, 0, 2871), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/neptune.bmp"),
		"Neptune", 60200.0f, 0.6f, vec::Vector3(0, 0, 4504), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/neptune.bmp"),
		"Pluto", 90600.0f, 0.6f, vec::Vector3(0, 0, 5913), 9.5f));
}

SolarSystem::~SolarSystem()
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		delete m_Planets[i];
	}
	free(sphere);
	delete(EarthSettings);
}

void SolarSystem::Load()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Load();
	}

	findPlanetByName("Earth").addMoon(25.0f, 0.6f);

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	glNewList(m_list + 1, GL_COMPILE);
		gluSphere(sphere, 1, 50, 50);
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
		if (i == 0) {
			glDisable(GL_LIGHTING);
			m_Planets[i]->Draw();
			glEnable(GL_LIGHTING);
		}
		else {
			m_Planets[i]->Draw();
			if(i == 3) {
				EarthSettings->drawText(m_Planets[i]->planetSettigs(), 
					vec::Vector3(20, 100), 1.0f);
			}
		}
	}
}

void SolarSystem::renderOrbits()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->renderOrbit();
	}

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

Planet& SolarSystem::findPlanetByName(const std::string& planetName)
{
	for (size_t planet_t = 0; planet_t < m_Planets.size(); planet_t++)
	{
		if(m_Planets[planet_t]->getPlanetName() == planetName){
			return *m_Planets[planet_t];
		}
	}
	IO::printError("No Planet Found With Name: {" + planetName + "}");
}
