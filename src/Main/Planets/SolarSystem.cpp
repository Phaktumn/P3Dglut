#include "SolarSystem.h"
#include "../../Misc/Debug/IO.h"
#include <Misc/RenderText.h>
#include <Main/Keyboard/Keyboard.h>
#include <Main/Game.h>

#define PLANETS 1
GLuint SolarSystem::m_list;

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
	free(sphere);
	delete Settings;
}

void SolarSystem::Load()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Load();
	}

	if (m_Planets.size() <= 1){
		//Do nothing
	}
	else{
		findPlanetByName("Earth").addMoon(25.0f, 0.6f);
	}

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	m_list = glGenLists(1);
	glNewList(m_list, GL_COMPILE);
		gluSphere(sphere, 1, 50, 50);
	glEndList();
}

void SolarSystem::Simulate(float deltaTime)
{
#ifdef PLANETS 0
	if (Keyboard::getKeyPressed(NUM_0))
	{
		m_print_Index = 0;
		m_last_PrintIndex = 0;
		Game::m_camera->setLookAt(
			m_Planets[m_print_Index]->getPositionVec());
	}
	if (Keyboard::getKeyPressed(NUM_1)) {
		m_print_Index = 1;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 1;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
	}
	if (Keyboard::getKeyPressed(NUM_2)) {
		m_print_Index = 2;
		if (m_last_PrintIndex != m_print_Index)
			m_Planets[m_last_PrintIndex]->setSelected(false);
		m_last_PrintIndex = 2;
		Game::m_camera->setLookAt(m_Planets[m_print_Index]->getPositionVec());
		m_Planets[m_print_Index]->setSelected(true);
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
	}
#endif
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
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	for (size_t i = 0; i < m_Planets.size(); i++) {
		//Se for o sol disable light
		if (i == 0) {
			glDisable(GL_LIGHTING);
			m_Planets[i]->Draw();
			glEnable(GL_LIGHTING);
		}
		//resto dos planetas enable Light
		else {
			glEnable(GL_LIGHTING);
			m_Planets[i]->Draw();
			glDisable(GL_LIGHTING);
		}
		if (i == m_print_Index) {
			Settings->drawText(m_Planets[i]->planetSettigs(),
				vec::Vector3(20, 150), 1.0f);
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void SolarSystem::renderOrbits() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->renderOrbit();
	}

	glDisable(GL_BLEND);
}

vec::Vector3 SolarSystem::getPlanetPostion(const int planetID) const
{
	int _ID = MathHelper::Clampi(planetID, 0, 9);
	return m_Planets[_ID]->getPositionVec();
}

Planet& SolarSystem::findPlanetByName(const std::string& planetName)
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
