#pragma once
#include <vector>
#include "Planet.h"

class SolarSystem
{
public:
	explicit SolarSystem(const int PlanetCount);
	~SolarSystem();

	void Load();
	void Simulate(float deltaTime);
	void Draw();

private: 
	GLuint m_list;
	std::vector<Planet> m_Planets;
};

