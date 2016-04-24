#ifndef _UNIVERSE_SIMULATOR_H_
#define _UNIVERSE_SIMULATOR_H_

#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#pragma once
#include "LoadBMP.h"
#include "List.h"
#include "Space/Planets/Universe.h"
#include "Space/Planets/SolarSystem.h"
#include "Space/Comet.h"
#include "FreeGlutWrap.h"

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
	List<Vector3*> SolarPositions;

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
		glDisable(GL_DEPTH_TEST); glDepthMask(GL_FALSE);
	    _Scale(Vector3(20000));
		Universe::drawQuads();
		glEnable(GL_DEPTH_TEST); glDepthMask(GL_TRUE);
		glEnable(GL_LIGHTING);
		glEndList();
	}

	void add_SolarSystem(SolarSystem* _Solar_System, Vector3* position)
	{
		SolarPositions.push_back(position);
		solarSystems.push_back(_Solar_System);
	}  

	void add_Comet_to_SolarSystem(const std::string& solaSystem_name, Comet* _comet)
	{
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			if(solarSystems[i]->getName() == solaSystem_name) {
				Comets.push_back(_comet);
				Comets[i]->load();
			}
		}
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
		for (size_t i = 0; i < Comets.size(); i++) {
			Comets[i]->simulate(deltaTime);
		}
	}
	
	void draw() const
	{
		drawUniverse();
		for (size_t i = 0; i < solarSystems.size(); i++){
			_glTranslate(*SolarPositions[i]);
			solarSystems[i]->Draw();
			solarSystems[i]->renderOrbits();
		}
		for (size_t i = 0; i < Comets.size(); i++){
			Comets[i]->draw();
			Comets[i]->renderOrbit();
		}
	}

	explicit UniverseSimulator()
		: m_simulate(false){
		load_Universe();
	}

	~UniverseSimulator()
	{
		for (auto i = 0; i < solarSystems.size(); i++) 
			delete SolarPositions[i];
		for (auto i = 0; i < solarSystems.size(); i++)
			delete solarSystems[i];
		for (auto i = 0; i < Comets.size(); i++)
			delete Comets[i];
	}

	void drawUniverse() const{
		glPushMatrix();
		glCallList(m_list);
		glPopMatrix();
	}
};

#endif

