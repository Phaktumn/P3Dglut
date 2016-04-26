#pragma once
#include <string>
#include <Vars/vec3f.h>
#include <Main/List.h>
#include <GL/freeglut.h>

using namespace std;
using namespace vec;

class UniverseObject
{
public:
	UniverseObject(const string& texturePath, const string& name, float orbitDuration, float rotationDuration, float eccentricity,
		const Vector3& pos, float scale, float orbitInclination, float planetInclination);

	virtual ~UniverseObject()
	{

	}

	virtual void load();
	virtual void simulate(float);
	virtual void draw();
	virtual void renderOrbit() const;
	virtual void loadTexture();

	virtual string& getName()
	{
		return m_Name;
	}
	/* Planet Position Debug String */
	string getPosition() const
	{
		return m_Position.debugString();
	}
	/* Planet Position vector*/
	Vector3& getPositionVec()
	{
		return m_Position;
	}
	float getInclination() const
	{
		return planetInclination;
	}

	float getScale() const
	{
		return this->m_scale;
	}
	/* Get if Planet is the selected ONE */
	bool IsSelected() const
	{
		return m_isSelected;
	}
	/* Set's the planet selected state */
	void setSelected(bool state) {
		if (m_isSelected == state) return;
		m_isSelected = state;
	}

	void setSphere(GLUquadric* sphere){
		this->sphere = sphere;
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, GL_TRUE);
		gluQuadricNormals(sphere, GLU_SMOOTH);
	}
	GLUquadricObj* sphere = nullptr;
protected:
	/* Display List */
	GLuint list;

	/* In What solar sistem this Object is present*/
	string m_solarSystem_ID;
	/* Selected state to let the user add moon's */
	bool m_isSelected = false;
	/* Object Name */
	string m_Name;
	/* Position relative to sun vector3(0,0,0) */
	Vector3 m_Position;
	float m_orbitInclination; //Orbit inclination In degrees

	/* Tex */
	string m_texture_path;
	/* Texture Id */
	GLuint m_idtexture;

	/* All orbit vertices */
	List<Vector3> m_orbitVertexes;
	float m_scale = 0;
	/* Display list index to draw Orbits */
	GLuint m_OrbitList;

	//Distance from planet 0,0,0
	/* Distance relative to this planet solar system Sun*/
	float m_Aphelion;
	//Actual distance from planet to 0,0,0
	/* Kepler Orbit Distance relative to this planet solar system Sun */
	float m_KeplerOrbitDistance = 0;
	float m_CurrPlanetInc = 0;
	float m_rotation;
	float m_orbit_Angle;
	float m_Orbit_Duration;
	float m_Rotation_Duration;
	float yaw = 0;
	/* Planet Inclination relative to solar Equator */
	float planetInclination;

	/* Calculates the distance to sun given an angle in radians */
	virtual float calculateKeplerOrbit(float radians);
	virtual Vector3& calculateHeight(float angle_x);

	/* Float Value used to calculate Kepler Orbit */
	float m_eccentricity;

	/*planet normal perpendicular to rotation axis*/
	Vector3 m_northPoleNormal;
};
