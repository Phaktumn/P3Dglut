#pragma once
#include "../Camera/Camera.h"
#include "../../Vars/Object.h"
#include "../../Misc/Physics/PhysicsObject.h"
#include "../../Misc/Physics/Mesh/AABB.h"

class Camera;

class Player
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void Draw() const;

	RigidBody& getRigidBody() const;
	PhysicsObject& getPhysicsObject() const { return *Box; }

private:
	AABB collider;
	Camera* camera;
	//Physics object
	Object* player;
	PhysicsObject* Box;
	float rotationAngle = 0;
};

