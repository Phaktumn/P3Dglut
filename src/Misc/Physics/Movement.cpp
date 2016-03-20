#include "Movement.h"


Transform::Transform(): mass(1250)
{
	position = vec::Vector3(0, 100, 0);
	rotation = vec::Vector3(0, 0, 0);
	Force = vec::Vector3::zero();
	gravity = 1; //1 = activado 0 = desativado
	collider = new SphereCollider(&position, 2);
}


Transform::~Transform()
{

}

void Transform::Move(float i, float deltaTime)
{
	//velocity.x = i + acceleration.x * rotation.x * deltaTime;
	//velocity.z = i + acceleration.y * rotation.x * deltaTime;

	//Force.x = mass * acceleration.x;
	//Force.z = mass * acceleration.y;

	//position.x += velocity.x * deltaTime;
	//position.z += velocity.z * deltaTime;

	//collider->Transform(&position);
}

void Transform::Rotate(float angle)
{
	rotation.x = sin(angle);
	rotation.z = -cos(angle);
}

void Transform::update(float deltaTime)
{
	if (gravity == 1) {
		velocity = acceleration * deltaTime;
		Force = Force + acceleration * MathHelper::normalizef(mass, 100000);
		position = position + Force * deltaTime;
#if _WITHOUT_TERRAIN_COLLISIONS 1
		if (position.y <= OFFSET) {
			position.y = OFFSET;
		}
#endif
	}
}

void Transform::isColliding(BoxCollider* collider) 
{
	if(this->collider->Intersects(collider)) {
		this->position.x = this->position.x - (0.1f * rotation.x);
		this->position.z = this->position.z - (0.1f * rotation.z);
	}
}
