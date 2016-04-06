#pragma once
#include <vector>
#include "Planet.h"

class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

	void Load();
	void Simulate(float deltaTime);
	void Draw() const;

	void renderOrbits();

	static GLuint m_list;

private: 
	std::vector<Planet*> m_Planets;
};

