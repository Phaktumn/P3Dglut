#pragma once
#include "../../Vars/Object.h"
#include "../../Misc/Physics/Movement.h"
#include "../Camera/Camera.h"

class BoxCollider;

class Camera;

class Player
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void Draw() const;

	Transform* getTranform() const
	{ return transform; }

	float get_rotation_angle() const { return rotationAngle; }

private:
	Camera* camera;
	Object* player;
	Transform* transform;
	float rotationAngle = 0;
};

