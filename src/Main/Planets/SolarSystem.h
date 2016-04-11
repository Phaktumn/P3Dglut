#pragma once
#include <vector>
#include "Planet.h"
#include <Misc/RenderText.h>

#define EC_MERCURY    0.2056
#define EC_VENUS      0.0068
#define EC_EARTH      0.0167
#define EC_MARS	      0.0934
#define EC_JUPITER    0.0483
#define EC_SATURN     0.0560
#define EC_URANUS     0.0461
#define EC_NEPTUNE    0.0097
#define EC_PLUTO      0.0103

class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

	void Load();
	void Simulate(float deltaTime);
	void preCameraTranslateDraw() const;
	void Draw() const;

	void renderOrbits();

	vec::Vector3 getPlanetPostion(const int planetID);
	Planet& findPlanetByName(const std::string& planetName);
	void addMoon();

	static GLuint m_list;

private: 
	std::vector<Planet*> m_Planets;
	GLUquadricObj* sphere = nullptr;
	RenderText* Settings = new RenderText();

	float simulationDeltaTime = 0.1f;

	GLuint m_Universetexture;
	void loadUniverTexture();

	int m_last_PrintIndex;
	int m_print_Index;
	float m_elapsedTime;
};

