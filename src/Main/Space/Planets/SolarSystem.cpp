#include "SolarSystem.h"
#include <Main/Keyboard/Keyboard.h>
#include <Misc/Debug/IO.h>

//************************************
// Method:    SolarSystem
// FullName:  SolarSystem::SolarSystem
// Access:    public 
// Parameter: const string & _name
//************************************
SolarSystem::SolarSystem(const string& _name)
{
	m_Name = _name;
	m_elapsedTime = 0;
	simulationDeltaTime = 0.03f;
}

SolarSystem::~SolarSystem()
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		delete m_Planets[i];
	}
	delete m_planet_settings_text;
}

void SolarSystem::Load() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->load();
	}
}

void SolarSystem::Simulate(float deltaTime)
{
	if (Keyboard::getKeyPressed(KEY_Z)) {
		simulationDeltaTime -= 0.001f;
		simulationDeltaTime = MathHelper::Clampf(simulationDeltaTime, 0.001f, 0.05f);
	}
	if (Keyboard::getKeyPressed(KEY_X)) {
		simulationDeltaTime += 0.001f;
		simulationDeltaTime = MathHelper::Clampf(simulationDeltaTime, 0.001f, 0.05f);
	}
	if (Keyboard::getKeyPressed(KEY_J)) {
		addMoon();
	}
	for (size_t i = 0; i < m_Planets.size(); i++){
		m_Planets[i]->simulate(simulationDeltaTime);
	}
}

void SolarSystem::Draw() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->draw();
	}
	m_planet_settings_text->drawText(m_Planets[m_SelectedIndex]->objectSettigs());
}

void SolarSystem::renderOrbits() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->renderOrbit();
	}
}

vec::Vector3 SolarSystem::getPlanetPostion(const int planetID) const
{
	int _ID = MathHelper::Clampi(planetID, 0, 9);
	return m_Planets[_ID]->getPositionVec();
}

// ReSharper disable once CppNotAllPathsReturnValue
Planet& SolarSystem::findPlanetByName(const string& planetName) const
{
	for (size_t planet_t = 0; planet_t < m_Planets.size(); planet_t++)
	{
		if(m_Planets[planet_t]->getName() == planetName){
			return *m_Planets[planet_t];
		}
	}
	IO::printError("No Planet Found With Name: {" + planetName + "}");
}

void SolarSystem::addMoon() const
{
	m_Planets[m_SelectedIndex]->addMoon(rand() % 100 + 10, rand() % 1 - 0.5f + 5);
}

void SolarSystem::addPlanet(UniverseObject* planet)
{
	m_Planets.push_back(static_cast<Planet*>(planet));
	findPlanetByName(planet->getName()).load();
}
