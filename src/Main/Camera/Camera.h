#ifndef CAMERA_H_
#define CAMERA_H_

#pragma once
#include "../../Vars/vec3f.h"
#include "../Player/Player.h"
 
class Player;
 
class Camera
{
public:
	//gluLookAt()
	explicit Camera(Player& player);
	explicit Camera(const vec::Vector3& position);
	explicit Camera();
	virtual ~Camera();

	//Sets the player to follow!
	Player* player;

	virtual void Update(float deltaTime);
	virtual void Draw() const;

	vec::Vector3 get_loook_at_vector3() const
	{ return this->m_lookAt; }

	virtual void setLookAt(const vec::Vector3& vec)
	{ this->m_lookAt = vec; }

	vec::Vector3 get_pos_vector3() const
	{ return this->eye; }

	vec::Vector3 get_up_vector3() const
	{ return this->upVec; }

	float get_rotationangle_() const 
	{ return rotationAngle; }

protected:
	vec::Vector3 m_lookAt;
	vec::Vector3 eye;
	vec::Vector3 upVec;

	vec::Vector3 rightVector;
	//vec::Vector3 upVec;
	vec::Vector3 forwardVec;

	vec::Vector3 m_Position;

	//Player angle rotation in Degrees
	float rotationAngle;
};

#endif


