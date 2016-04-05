#pragma once
#include "src/Vars/vec3f.h"
#include "src/Main/Planets/Planet.h"

class Planet;

class Moon
{
public:
 	explicit Moon(Planet& planet,float distanceToPLanet);
	~Moon();

	void Update(float deltaTime);
	void Draw() const;

	vec::Vector3 m_position;
	float m_distance_to_planet;

private:
	Planet& planet_;
};

