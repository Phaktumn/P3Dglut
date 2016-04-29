#pragma once
#include <vector>
#include "Planet.h"
#include <Misc/RenderText.h>
#include <Main/List.h>

#define EC_MERCURY    0.2056
#define EC_VENUS      0.0068
#define EC_EARTH      0.0167
#define EC_MARS	      0.0934
#define EC_JUPITER    0.0483
#define EC_SATURN     0.0560
#define EC_URANUS     0.0461
#define EC_NEPTUNE    0.0097
#define EC_PLUTO      0.0103


class SolarSystem
{
public:
	explicit SolarSystem(const string& _name);
	~SolarSystem();

	string& getType()
	{ return TYPE; }

	void Load() const;
	void Simulate(float deltaTime);
	void Draw() const;

	void renderOrbits() const;

	Vector3 getPlanetPostion(const int planetID) const;

	/* Finds a planet with the given Name */
	Planet& findPlanetByName(const string& planetName) const;

	/* Adds a Moon to selected planet
	* Unable to select planets (input disabled) 
	*/
	void addMoon() const;
	/* Adds a planet to this* Solar system  */
	void addPlanet(UniverseObject* planet);

	/* Returns this Solar System Name */
	string& getName() { return m_Name; }

	void setSelectedObject(const int Index)
	{
		if (m_SelectedIndex >= m_Planets.size()) return;
		m_SelectedIndex = Index;
	}

	int getSelected() const
	{
		return m_SelectedIndex;
	}

	Planet* getPlanet(int _i) const
	{
		return m_Planets[_i];
	}

	void setOrbitRenderState(const short int _state)
	{
		if (_state == m_renderOrbitState) return;
		m_renderOrbitState = _state;
		MathHelper::Clampi(m_renderOrbitState, 0, 1);
	}
private:

	short int m_renderOrbitState = 1;

	int m_SelectedIndex = 0;
	string TYPE = "Solar System";

	List<Planet*> m_Planets;
	RenderText* m_planet_settings_text = new RenderText(Vector3(25, 150), 1.0f);

	float simulationDeltaTime = 0.1f;

	string m_Name;
	float m_elapsedTime;
};

