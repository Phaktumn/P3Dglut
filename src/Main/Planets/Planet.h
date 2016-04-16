#pragma once
#include "../../Vars/vec3f.h"
#include <GL/freeglut.h>
#include <Main/List.h>

class Moon;

class Planet
{
public:
	explicit Planet(const std::string& modelPath, const  std::string& name,
		float orbitDuration, float rotatioDuration, float eccentricity, const vec::Vector3& pos, float scale);
	~Planet();
	void Load();
	void Simulate(float deltaTime);
	void Draw() const;

	void loadTexture();
	void addMoon(float distanceToPlanet, float radius);
	void renderOrbit() const;

	/* Number Of Moons */
	int getMoonCount() const
	{ return m_moon_index; }

	/* Planet Name */
	std::string& getName()
	{ return m_Name; }

	/* Planet Position Debug String */
	std::string getPosition() const
	{ return m_Position.debugString(); }

	/* Planet Position vector*/
	vec::Vector3& getPositionVec()
	{ return m_Position; }

	/* Get if Planet is the selected ONE */
	bool IsSelected() const
	{ return m_isSelected; }

	/* Set's the planet selected state */
	void setSelected(bool state){
		if (m_isSelected == state) return;
		m_isSelected = state;
	}

	/* Get object Type */
	std::string& getType() 
	{ return TYPE; }

	std::string& planetSettigs();
	static GLuint list;
	GLuint m_OrbitList;

private:
	GLUquadricObj* sphere = nullptr;

	/* In What solar sistem this planet is present*/
	std::string m_solarSystem_ID;

	std::string TYPE = "Planet";

	/* Selected state to let the user add moon's */
	bool m_isSelected = false;

	std::string m_texture_path;
	std::string m_Name;
	/* Position relative to sun vector3(0,0,0) */
	vec::Vector3 m_Position;
	float m_orbitInclination; //Orbit inclination In degrees
	std::string m_planetSettings;

	GLuint m_idtexture;
	/* All orbit vertices */
	List<vec::Vector3> orbitVerices;

	float m_scale = 0;

	//Distance from planet 0,0,0
	/* Distance relative to this planet solar system Sun*/
	float m_orbit_distance;

	//Actual distance from planet to 0,0,0
	/* Kepler Orbit Distance relative to this planet solar system Sun */
	float m_KeplerOrbitDistance = 0;

	float m_rotation;
	float m_orbit_Angle;
	float m_Orbit_Duration;
	float m_Rotation_Duration;

	float calculateKeplerOrbit(float radians);
	float m_eccentricity;

	int m_moon_index = 0;
	List<Moon*> moons;

	/* Days Elapsed in Earth Since simulation has started */
	int m_days_elapsed = 0;
	int m_years_elapsed = 0;
};

