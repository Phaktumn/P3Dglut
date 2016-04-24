#ifndef COMET_H
#define COMET_H

#pragma once
#include <Vars/vec3f.h>
#include "UniverseObject.h"

class Comet
	: public UniverseObject
{
public:
	Comet(const string& texturePath, const  string& name,
		float orbitDuration, float rotatioDuration, float eccentricity,
		const Vector3& pos, float scale, float orbitInclination, float planetInclination);

	void load() override;
	void simulate(float simulationDelta) override;
	void draw() override;
	void renderOrbit() const override;

	/* Get object Type */
	string& getType()
	{return TYPE;}

private:
	string TYPE = "Comet";
};

#endif

