#pragma once
#include "../../Vars/vec3f.h"
#include "../../Misc/Physics/PhysicsObject.h"
#include "../../Vars/Object.h"

class Planet
{
public:
	explicit Planet(std::string& modelPath, std::string& name, 
		float orbitDuration, float rotatioDuration, vec::Vector3& pos, float scale);
	~Planet();
	void Load();
	void Simulate(float deltaTime);
	void Draw() const;

	std::string getPosition() const{
		return m_Position.debugString();
	}

private:
	std::string m_Name;
	vec::Vector3 m_Position;
	PhysicsObject m_planet_object_;
	Object m_Sphere;

	float m_scale = 0;

	float m_orbit_distance;
	float m_rotation;
	float m_orbit_Angle;
	float m_Orbit_Duration;
	float m_Rotation_Duration;
};

