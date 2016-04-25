#ifndef MOON_H_
#define MOON_H_

#pragma once
#include <Main/List.h>
#include <Vars/vec3f.h>
#include <Main/Space/UniverseObject.h>

class Planet;

class Moon : public UniverseObject
{
public:
 	explicit Moon(const string& texturePath, const  string& name,
		float orbitDuration, float rotatioDuration, float eccentricity,
		const Vector3& pos, float scale, float orbitInclination, float planetInclination, 
		Planet& planet, float distanceToPLanet);
	~Moon();

	void load() override;
	void simulate(float deltaTime) override;
	void draw() override;
	void renderOrbit() const override;

	/* Get object Type*/
	const string& getType() const
	{ return TYPE; }

	/* Get tha planet */
	Planet& getPlanet() const
	{ return planet_; }

	/* Get distance to planet */
	float getDistanceFromPlanet() const
	{ return m_distance_to_planet; }

private:
	//Moon Specific Vars----------------------------
	/* Planet that this moon is attached to */
	Planet& planet_;
	string TYPE = "Moon";
	float m_distance_to_planet;
	//---------------------------------------------
};

#endif
