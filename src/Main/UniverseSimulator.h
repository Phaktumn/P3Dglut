#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#pragma once
#include "Planets/SolarSystem.h"
#include "LoadBMP.h"
#include "Planets/Universe.h"
#include "List.h"

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
		glDisable(GL_DEPTH);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(0);
		glScalef(10000, 10000, 10000);
		Universe::drawQuads();
		glDepthMask(1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH);
		glPopMatrix();
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
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			solarSystems[i]->Simulate(deltaTime);
		}
	}
	
	void draw() const
	{
		drawUniverse();
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			glTranslatef(SolarPositions[i]->x, SolarPositions[i]->y, SolarPositions[i]->z);
			solarSystems[i]->Draw();
			solarSystems[i]->renderOrbits();
		}
	}

	UniverseSimulator(): m_simulate(false)
	{
		load_Universe();
	}

	~UniverseSimulator()
	{
		
	}

	void drawUniverse() const
	{
		//2
		glDisable(GL_LIGHTING);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, m_Universetexture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glPushMatrix();
		glCallList(m_list);
		//glPopMatrix();
	}
};

