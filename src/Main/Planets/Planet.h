#pragma once
#include "../../Vars/vec3f.h"
#include "../../Misc/Physics/PhysicsObject.h"
#include <vector>
#include "../../LoadTGAs/Texture.h"

class Moon;

bool LoadTGA(Texture *, char *);

class Planet
{
public:
	explicit Planet(const std::string& modelPath, const  std::string& name,
		float orbitDuration, float rotatioDuration, vec::Vector3& pos, float scale);
	~Planet();
	void Load();
	void Simulate(float deltaTime);
	void Draw() const;

	void loadTexture();
	void addMoon(float distanceToPlanet, float radius);
	void renderOrbit();

	std::string& getPlanetName(){
		return m_Name;
	}

	std::string getPosition() const{
		return m_Position.debugString();
	}

	vec::Vector3& getPositionVec(){
		return m_Position;
	}

	void setList(GLuint _list){
		list = _list;
	}

private:
	std::string m_texture_path;
	Texture m_texture;
	std::string m_Name;
	vec::Vector3 m_Position;

	GLuint m_idtexture;
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

