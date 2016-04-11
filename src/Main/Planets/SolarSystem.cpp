#include "SolarSystem.h"
#include "../../Misc/Debug/IO.h"
#include <Misc/RenderText.h>
#include <Main/Keyboard/Keyboard.h>
#include <Main/Game.h>
#include "Universe.h"
#include <Main/LoadBMP.h>

GLuint SolarSystem::m_list;

SolarSystem::SolarSystem() 
	: m_Universetexture(0)
{
	m_Planets.push_back(new Planet("Textures/sun.bmp",
		"Sun", NULL, NULL,NULL, vec::Vector3(0, 0, 0), 20));

	m_Planets.push_back(new Planet("Textures/mercury.bmp", 
		"Mercurio", 88.0f, 58.0f,EC_MERCURY, vec::Vector3(0, 0, 70), 0.3f));

	m_Planets.push_back(new Planet(std::string("Textures/earth.bmp"), 
		"Venus", 225.0f, 241.0f,EC_VENUS, vec::Vector3(0, 0, 108), 0.4f));
	
	m_Planets.push_back(new Planet(std::string("Textures/earth.bmp"),
		"Earth", 365.0f, 1.0f,EC_EARTH, vec::Vector3(0, 0, 150), 1.0f));
	
	m_Planets.push_back(new Planet(std::string("Textures/mars.bmp"),
		"Mars", 687.0f, 1.01f,EC_MARS, vec::Vector3(0, 0, 228), 0.9f));

	m_Planets.push_back(new Planet(std::string("Textures/jupiter.bmp"),
		"Jupiter", 4332.0f, 9.8 / 24.0, EC_JUPITER, vec::Vector3(0, 0, 772), 11.5f));
	
	m_Planets.push_back(new Planet(std::string("Textures/saturn.bmp"),
		"Saturn", 10760.0f, 10.5 / 24.0, EC_SATURN,vec::Vector3(0, 0, 1443), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/uranus.bmp"),
		"Uranus", 30700.0f, 17.0 / 24.0, EC_URANUS,vec::Vector3(0, 0, 2871), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/neptune.bmp"),
		"Neptune", 60200.0f, 16.0 / 24.0, EC_NEPTUNE,vec::Vector3(0, 0, 4504), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/neptune.bmp"),
		"Pluto", 90600.0f,EC_PLUTO, 0.6f, vec::Vector3(0, 0, 5913), 9.5f));

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

	loadUniverTexture();

	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->Load();
	}

	findPlanetByName("Earth").addMoon(25.0f, 0.6f);

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	m_list = glGenLists(2);
	glNewList(m_list, GL_COMPILE);
		gluSphere(sphere, 1, 50, 50);
	glEndList();

	glNewList(m_list + 1, GL_COMPILE);
		glDisable(GL_DEPTH);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(0);
		glScalef(10000, 10000, 10000);
		Universe::drawQuads();
		glDepthMask(1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH);
		glEndList();
	glDisable(GL_TEXTURE_2D);
}

void SolarSystem::Simulate(float deltaTime)
{
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
	glBindTexture(GL_TEXTURE_2D, m_Universetexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPushMatrix();
	glCallList(m_list + 1);
	glPopMatrix();

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

void SolarSystem::renderOrbits()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	for (size_t i = 0; i < m_Planets.size(); i++) {
		m_Planets[i]->renderOrbit();
	}

	glDisable(GL_BLEND);
}

vec::Vector3 SolarSystem::getPlanetPostion(const int planetID)
{
	int _ID = MathHelper::Clampi(planetID, 0, 9);
	return m_Planets[_ID]->getPositionVec();
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

void SolarSystem::addMoon()
{
	for (size_t planet_t = 0; planet_t < m_Planets.size(); planet_t++)
	{
		if(m_Planets[planet_t]->IsSelected() == true)
			m_Planets[planet_t]->addMoon(rand() % 100 + 10, rand() % 1 - 0.5f + 5);
	}
}

/* Load Universe Texture */
void SolarSystem::loadUniverTexture()
{
	m_Universetexture = _loadBMP("Textures/stars.bmp");
}
