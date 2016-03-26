#pragma once
#include "../../Vars/vec3f.h"
#include "../Player/Player.h"
 
class Player;
 
class Camera
{
public:
	//gluLookAt()
	explicit Camera(Player& player);
	~Camera();

	//Sets the player to follow!
	Player* player;

	void Update(float deltaTime);
	void Draw() const;

	vec::Vector3 get_loook_at_vector3() const
	{ return this->lookAt; }

	vec::Vector3 get_pos_vector3() const
	{ return this->eye; }

	vec::Vector3 get_up_vector3() const
	{ return this->upVec; }

	float get_rotationangle_() const 
	{ return rotationAngle; }

private:
	vec::Vector3 lookAt;
	vec::Vector3 eye;
	vec::Vector3 upVec;

	//Player angle rotation in Degrees
	float rotationAngle;
};

