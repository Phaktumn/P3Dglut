#pragma once
#include "../../Vars/vec3f.h"
#include "../Player/Player.h"
 
class Player;
 
class Camera
{
public:
	//gluLookAt()
	explicit Camera(Player& player);
	explicit Camera(vec::Vector3& position, float rotationAngle);
	virtual ~Camera();

	//Sets the player to follow!
	Player* player;

	virtual void Update(float deltaTime);
	virtual void Draw() const;

	vec::Vector3 get_loook_at_vector3() const
	{ return this->lookAt; }

	vec::Vector3 get_pos_vector3() const
	{ return this->eye; }

	vec::Vector3 get_up_vector3() const
	{ return this->upVec; }

	float get_rotationangle_() const 
	{ return rotationAngle; }

protected:
	vec::Vector3 lookAt;
	vec::Vector3 eye;
	vec::Vector3 upVec;

	//Player angle rotation in Degrees
	float rotationAngle;
};
