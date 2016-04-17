#include "SolarSystem.h"
#include <Main/Keyboard/Keyboard.h>
#include <Misc/Debug/IO.h>

SolarSystem::SolarSystem(const std::string& _name)
{
	//Add Only a sun to each System created
	m_Planets.push_back(new Planet("Textures/sun.bmp",
		"Sun", NULL, NULL,NULL, vec::Vector3(0, 0, 0), 20));

	m_Name = _name;
	m_print_Index = 0;
	m_last_PrintIndex = 0;
	m_elapsedTime = 0;
	simulationDeltaTime = 0.01f;
}

SolarSystem::~SolarSystem()
{
	for (size_t i = 0; i < m_Planets.size(); i++){
		delete m_Planets[i];
	}
	delete Settings;
}

void SolarSystem::Load() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Load();
	}
}

void SolarSystem::Simulate(float deltaTime)
{
	/*if (Keyboard::getKeyPressed(NUM_1)) {
		m_print_Index = 1;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 1;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_2)) {
		if (m_Planets.size() < 2) {
			m_print_Index = 2;
			if (m_last_PrintIndex != m_print_Index)
				m_Planets[m_last_PrintIndex]->setSelected(false);
			m_last_PrintIndex = 2;
			Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
			m_Planets[m_print_Index]->setSelected(true);
		}
	}
	if (Keyboard::getKeyPressed(NUM_3)) {
		m_print_Index = 3;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 3;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_4)) {
		m_print_Index = 3;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 3;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_5)) {
		m_print_Index = 5;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 5;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_6)) {
		m_print_Index = 6;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 6;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_7)) {
		m_print_Index = 7;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 7;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_8)){
		m_print_Index = 8;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 8;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_9)) {
		m_print_Index = 9;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 9;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}*/
	if (Keyboard::getKeyPressed(KEY_Z)) {
		simulationDeltaTime -= 0.01f;
		simulationDeltaTime = MathHelper::Clampf(simulationDeltaTime, 0.0001f, 1.0f);
	}
	if (Keyboard::getKeyPressed(KEY_X)) {
		simulationDeltaTime += 0.01f;
		simulationDeltaTime = MathHelper::Clampf(simulationDeltaTime, 0.0001f, 1.0f);
	}
	if (Keyboard::getKeyPressed(KEY_J)) {
		addMoon();
	}

	for (size_t i = 0; i < m_Planets.size(); i++){
		m_Planets[i]->Simulate(simulationDeltaTime);
	}
}

void SolarSystem::Draw() const
{
	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Draw();
	}
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

Planet& SolarSystem::findPlanetByName(const std::string& planetName) const
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
	for (size_t planet_t = 0; planet_t < m_Planets.size(); planet_t++)
	{
		if(m_Planets[planet_t]->IsSelected() == true)
			m_Planets[planet_t]->addMoon(rand() % 100 + 10, rand() % 1 - 0.5f + 5);
	}
}

void SolarSystem::addPlanet(Planet* planet)
{
	m_Planets.push_back(planet);
	findPlanetByName(planet->getName()).Load();
}
