#pragma once
#include "../Camera/Camera.h"
#include "../../Vars/Object.h"
#include "../../Misc/Physics/PhysicsObject.h"

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
	Camera* camera;
	Object* player;
	PhysicsObject* Box;
	float rotationAngle = 0;
};

