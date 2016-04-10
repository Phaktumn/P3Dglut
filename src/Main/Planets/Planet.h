#pragma once
#include "../../Vars/vec3f.h"
#include <vector>
#include "../../LoadTGAs/Texture.h"

class Moon;

bool LoadTGA(Texture *, char *);

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
	void renderOrbit();

	/* Number Of Moons */
	int getMoonCount() const
	{ return m_moon_index; }

	/* Planet Name */
	std::string& getPlanetName()
	{ return m_Name; }

	/* Planet Position Debug String */
	std::string getPosition() const
	{ return m_Position.debugString(); }

	/* Planet Position vector*/
	vec::Vector3& getPositionVec()
	{ return m_Position; }

	/* display list */
	void setList(GLuint _list)
	{ list = _list; }

	std::string& planetSettigs();

private:
	std::string m_texture_path;
	Texture m_texture;
	std::string m_Name;
	vec::Vector3 m_Position;
	float m_orbitInclination; //Orbit inclination In degrees
	std::string m_planetSettings;

	GLuint m_idtexture;
	GLuint list;

	float m_scale = 0;

	//Distance from planet 0,0,0
	float m_orbit_distance;
	//Actual distance ftom planet to 0,0,0
	float m_KeplerOrbitDistance = 0;

	float m_rotation;
	float m_orbit_Angle;
	float m_Orbit_Duration;
	float m_Rotation_Duration;

	float calculateKeplerOrbit(float radians);
	float m_eccentricity;

	int m_moon_index = 0;
	std::vector<Moon*> moons;

	/* Days Elapsed in Earth Since simulation has started */
	int m_days_elapsed = 0;
	int m_years_elapsed = 0;
};

