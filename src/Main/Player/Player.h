#pragma once
#include "../../Vars/Object.h"
#include "../../Misc/Physics/Movement.h"

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw() const;
	void isColliding(BoxCollider* collider) const;
private:

	Object* player;
	Transform* transform;
	float rotationAngle = 0;
};

