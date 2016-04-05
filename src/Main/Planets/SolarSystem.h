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

private: 
	GLuint m_list;
	std::vector<Planet> m_Planets;
};

