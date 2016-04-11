#pragma once
#include "../../Vars/vec3f.h"
#include <GL/freeglut.h>
#include <vector>

class Planet;

class Moon
{
public:
 	explicit Moon(Planet& planet,
		float distanceToPLanet, float scale, float orbitAngle);
	~Moon();

	void Load();
	void Update(float deltaTime);
	void Draw() const;

	vec::Vector3 m_position;
	float m_distance_to_planet;

	void renderOrbit() const;

private:
	/* Store all orbit vertexes in this list*/
	std::vector<vec::Vector3> m_orbitVertexes;
	/* Orbit draw list */
	GLuint m_orbitList;

	/*Orbit Angle*/
	float m_orbit_angle = 0;
	/*Rotation Arround the Planet*/
	float m_rotation_angle = 0;
	/*Planet Size*/
	float m_planet_scale = 0;
	/*Planet the moon´s are attached to*/
	Planet& planet_;
	/*planet normal perpendicular to rotation axis*/
	vec::Vector3 m_northPoleNormal;
};

