#pragma once
#include <vector>
#include "Planet.h"
#include <Misc/RenderText.h>
#include <Main/List.h>

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
	SolarSystem(const std::string& _name);
	~SolarSystem();

	std::string& getType()
	{ return TYPE; }


	void Load();
	void Simulate(float deltaTime);
	//void preCameraTranslateDraw() const;
	void Draw() const;

	void renderOrbits() const;

	vec::Vector3 getPlanetPostion(const int planetID) const;
	Planet& findPlanetByName(const std::string& planetName);
	void addMoon() const;
	void addPlanet(Planet* planet);

	static GLuint m_list;

	std::string& getName() { return m_Name; }

private: 
	std::string TYPE = "Solar System";

	List<Planet*> m_Planets;
	//std::vector<Planet*> m_Planets;
	GLUquadricObj* sphere = nullptr;
	RenderText* Settings = new RenderText();

	float simulationDeltaTime = 0.1f;

	std::string m_Name;
	int m_last_PrintIndex;
	int m_print_Index;
	float m_elapsedTime;
};

