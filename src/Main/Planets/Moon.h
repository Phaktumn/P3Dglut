#pragma once
#include "../../Vars/vec3f.h"

class Planet;

class Moon
{
public:
 	explicit Moon(Planet& planet,float distanceToPLanet, float scale);
	~Moon();

	void Load();
	void Update(float deltaTime);
	void Draw() const;

	vec::Vector3 m_position;
	float m_distance_to_planet;

private:
	float m_rotation_angle = 0;
	float m_planet_scale = 0;
	Planet& planet_;

	vec::Vector3 m_northPoleNormal;
};

