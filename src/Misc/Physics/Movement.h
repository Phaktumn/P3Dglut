#pragma once
#include "../../Vars/vec3f.h"
#include "../Collisions/SphereCollider.h"
#include "RigidBody.h"

#define SPEED_MODIFIER                 0.01
#define GRAVITY                        -9.8
#define COLLISIONS_ENABLED             0
#define _WITHOUT_TERRAIN_COLLISIONS    1
#define OFFSET                         0.3

class Transform
{
public:
	Transform();
	~Transform();

	void Move(float x) const;
	void Rotate(float angle);

	vec::Vector3 getPosition() const
	{ return position; }
	vec::Vector3 getRotation() const
	{ return rotation; }
	void update(float deltaTime);
	void isColliding(BoxCollider& collider);

	int isGravity() const { return gravity; }
	vec::Vector3 linearRot;
	RigidBody* body;

private:
	vec::Vector3 velocity = vec::Vector3();
	vec::Vector3 acceleration = vec::Vector3(0, GRAVITY, 0);

	vec::Vector3 position;
	vec::Vector3 rotation;
	vec::Vector3 Force;

	SphereCollider* collider;

	float mass;

	float speed = 10;
	int gravity = 0;
};

