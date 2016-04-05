#pragma once
#include "../../Vars/vec3f.h"
#include "../../Misc/Physics/PhysicsObject.h"
#include "../../Vars/Object.h"
#include <vector>

class Moon;

class Planet
{
public:
	explicit Planet(std::string& modelPath, std::string& name, 
		float orbitDuration, float rotatioDuration, vec::Vector3& pos, float scale);
	~Planet();
	void Load() const;
	void Simulate(float deltaTime);
	void Draw() const;

	void addMoon(Moon* moon);

	std::string getPosition() const{
		return m_Position.debugString();
	}

	vec::Vector3& getPositionVec(){
		return m_Position;
	}

	void setList(GLuint _list){
		list = _list;
	}

	Object& getObject() const{
		return *m_Sphere;
	}

private:
	std::string m_Name;
	vec::Vector3 m_Position;
	PhysicsObject* m_planet_object_;
	Object* m_Sphere;

	GLuint list;

	float m_scale = 0;

	float m_orbit_distance;
	float m_rotation;
	float m_orbit_Angle;
	float m_Orbit_Duration;
	float m_Rotation_Duration;

	int m_moon_index = 0;
	std::vector<Moon*> moons;
};

