#pragma once
#include <vector>
#include "Planet.h"
#include <Misc/RenderText.h>

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

	Planet& findPlanetByName(const std::string& planetName);

	static GLuint m_list;

private: 
	std::vector<Planet*> m_Planets;
	GLUquadricObj* sphere = nullptr;
	RenderText* Settings = new RenderText();

	GLuint m_Universetexture;
	void loadUniverTexture();

	int m_print_Index;
	float m_elapsedTime;
};

