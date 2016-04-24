#ifndef PLANET_H_
#define PLANET_H_

#pragma once
#include <Main/List.h>
#include <Vars/vec3f.h>
#include "Moon.h"
#include <Main/Space/UniverseObject.h>

using namespace vec;

class Ring;

class Planet
	: public UniverseObject

{
public:
	Planet();
	explicit Planet(const string& texturePath, const  string& name,
		float orbitDuration, float rotatioDuration, float eccentricity, 
		const Vector3& pos, float scale, float orbitInclination, float planetInclination);
	~Planet();
	void load() override;
	void simulate(float deltaTime) override;
	void draw() override;

	void renderOrbit() const override;

	//Planet Specific Methods-----------------------
	void addMoon(float distanceToPlanet, float radius);
	void addRings(float innerRadius, float outterRadius);
	/* Number Of Moons */
	int getMoonCount() const
	{ return m_moon_index; }
	/* Get object Type*/
	string& getType() 
	{ return TYPE; }
	/* String with all the information about this Universe Object */
	string& objectSettigs();
	//-----------------------------------------------

private:
	//Planet Specific Vars----------------------------
	Ring* ring;
	string TYPE = "Planet";
	int m_moon_index = 0;
	List<UniverseObject*> moons;
	
	/* Days Elapsed in this planet Since simulation has started */
	int m_days_elapsed = 0;
	/* Years Elapsed in this planet Since simulations has starte */
	int m_years_elapsed = 0;
	string m_planetSettings;
	//---------------------------------------------------

	/*GLUquadricObj* sphere = nullptr;
	/* In What solar sistem this planet is present*/
	//string m_solarSystem_ID;
	/* Selected state to let the user add moon's */
	//bool m_isSelected = false;
	/* Tex */
	//string m_texture_path;
	/* Object Name */
	//string m_Name;
	/* Position relative to sun vector3(0,0,0) */
	//Vector3 m_Position;
	//float m_orbitInclination; //Orbit inclination In degrees
	//string m_planetSettings;
	/* Texture Id */
	//GLuint m_idtexture;
	/* All orbit vertices */
	//List<Vector3> m_orbitVertexes;
	//float m_scale = 0;
	//Distance from planet 0,0,0
	/* Distance relative to this planet solar system Sun*/
	//float m_Aphelion;
	//Actual distance from planet to 0,0,0
	/* Kepler Orbit Distance relative to this planet solar system Sun */
	//float m_KeplerOrbitDistance = 0;
	//float m_CurrPlanetInc = 0;
	//float m_rotation;
	//float m_orbit_Angle;
	//float m_Orbit_Duration;
	//float m_Rotation_Duration;
	//float yaw = 0;
	/* Planet Inclination relative to solar Equator */
	//float planetInclination;
	/* Calculates the distance to sun given an angle in radians */
	//float calculateKeplerOrbit(float radians);
	//Vector3& calculateHeight(float deltaTime,float angle_x) const;
	/* Float Value used to calculate Kepler Orbit */
	//float m_eccentricity; 
};
#endif


