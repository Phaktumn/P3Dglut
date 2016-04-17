#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#pragma once
#include "LoadBMP.h"
#include "List.h"
#include "Space/Planets/Universe.h"
#include "Space/Planets/SolarSystem.h"
#include "Space/Comet.h"

class UniverseSimulator
{
public:
	//All Objects In Universe!
	bool m_simulate;
	bool _getSimulateState() const
	{ return m_simulate; }

	GLuint m_Universetexture;
	GLuint m_list;
	List<SolarSystem*> solarSystems;
	List<Comet*> Comets;
	List<vec::Vector3*> SolarPositions;

	void load_Universe()
	{
		m_Universetexture = _loadBMP("Textures/stars.bmp");
		m_list = glGenLists(1);
		glNewList(m_list, GL_COMPILE);	
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_Universetexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPushMatrix();
		glScalef(10000, 10000, 10000);
		Universe::drawQuads();
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glEndList();
	}

	void add_SolarSystem(SolarSystem* _Solar_System, vec::Vector3* position){
		SolarPositions.push_back(position);
		solarSystems.push_back(_Solar_System);
	}

	void addPlanet_to_SolarSystem(const std::string& _solarSistemName, Planet* _planetToAdd) const
	{
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			if(solarSystems[i]->getName() == _solarSistemName) {
				solarSystems[i]->addPlanet(_planetToAdd);
			}
		}
	}

	void simulate(float deltaTime) const
	{
		for (size_t i = 0; i < solarSystems.size(); i++){
			solarSystems[i]->Simulate(deltaTime);
		}
		for (size_t i = 0; i < Comets.size(); i++){
			Comets[i]->simulate(deltaTime);
		}
	}
	
	void draw() const
	{
		drawUniverse();
		for (size_t i = 0; i < solarSystems.size(); i++){
			glTranslatef(SolarPositions[i]->x, SolarPositions[i]->y, SolarPositions[i]->z);
			solarSystems[i]->Draw();
			solarSystems[i]->renderOrbits();
		}
		for (size_t i = 0; i < Comets.size(); i++){
			Comets[i]->draw();
			Comets[i]->renderOrbit();
		}
	}

	explicit UniverseSimulator()
		: m_simulate(false)
	{
		load_Universe();
		Comets.push_back(
			new Comet("Textures/Earth.bmp", "Halley", 
				vec::Vector3(0, 0, 3200), 0.967, 75.3f, 0.0f, 0.4f));
		Comets[0]->load();
	}

	~UniverseSimulator()
	{
		
	}

	void drawUniverse() const{
		glCallList(m_list);
	}
};

