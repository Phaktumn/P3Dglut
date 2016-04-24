#include "Comet.h"

Comet::Comet(const string& texturePath, const string& name, float orbitDuration, float rotatioDuration,
	float eccentricity, const Vector3& pos, float scale, float orbitInclination, float planetInclination)
	: UniverseObject(texturePath, name, orbitDuration, rotatioDuration, eccentricity
		,pos, scale, orbitInclination, planetInclination)
{

}

void Comet::load()
{
	UniverseObject::load();
}

void Comet::simulate(float simulationDelta)
{
	UniverseObject::simulate(simulationDelta);
}

void Comet::draw()
{
	UniverseObject::draw();
}

void Comet::renderOrbit() const
{
	UniverseObject::renderOrbit();
}
