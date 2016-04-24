#ifndef COMET_H
#define COMET_H

#pragma once
#include <Vars/vec3f.h>
#include <GL/freeglut.h>
#include <Main/List.h>

class Comet
{
public:
	Comet(const std::string& texturePath, const  std::string& name,
		const vec::Vector3& position,
		const float m_eccentricity, const float m_orbit_duration,
		const float m_rotation_duration, float scale);

	void load();
	void simulate(float simulationDelta);
	void draw() const;
	void renderOrbit() const;

	/* Returns Comet Name */
	std::string& getName()
	{
		return m_Name;
	}

	/* Planet Position Debug String */
	std::string getPosition() const
	{
		return m_Position.debugString();
	}

	/* Planet Position vector*/
	vec::Vector3& getPositionVec()
	{
		return m_Position;
	}

	/* In What solar sistem this Comet is present*/
	std::string m_solarSystem_ID;

	/* Get if Planet is the selected ONE */
	bool IsSelected() const
	{
		return m_isSelected;
	}

	/* Set's the planet selected state */
	void setSelected(bool state) 
	{
		if (m_isSelected == state) return;
		m_isSelected = state;
	}
	/* Get object Type */
	std::string& getType()
	{
		return TYPE;
	}

private:
	/* Sphere That Represents this Object*/
	GLUquadricObj* sphere = nullptr;

	GLuint m_OrbitList;
	GLuint list;

	std::string TYPE = "Comet";

	/* Comet Selected State to Further use */
	bool m_isSelected;
	int m_orbitInclination;
	std::string m_Texture_Path;
	/* Texture ID*/
	GLuint m_idtexture;
	/* All orbit vertices */
	List<vec::Vector3> orbitVerices;

	/* Calculates the distance to sun given an angle in radians */
	float calculateKeplerOrbit(float radians);
	//Actual distance from planet to 0,0,0
	/* Kepler Orbit Distance relative to this planet solar system Sun */
	float m_KeplerOrbitDistance = 0;

	/* Initial Comet Position 
	   z value will be m_distanceToSun
	   that corresponds to Aphelion
	*/
	vec::Vector3 m_Position;
	/* Comet Eccentricity used to calculate Kepler orbit*/
	const float m_eccentricity;

	/* Comet Name */
	std::string m_Name;

	float m_orbitDuration;
	float m_rotationDuration;
	float m_size;
	float m_Aphelion;
	float m_orbit_Angle;
};

#endif

