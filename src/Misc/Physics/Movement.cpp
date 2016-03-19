#include "Movement.h"


Transform::Transform(): mass(0)
{
	position = new vec::Vector3(0, 15, 0);
	rotation = new vec::Vector3(0, 0, 0);
	gravity = 1; //1 = activado 0 = desativado
	collider = new SphereCollider(position, 2);
}


Transform::~Transform()
{

}

void Transform::Move(float i, float deltaTime)
{
	velocity.x = i + _gravity_vec->x * deltaTime;
	velocity.z = i + _gravity_vec->z * deltaTime;

	position->x += velocity.x * rotation->x * deltaTime;
	position->z += velocity.z * rotation->z * deltaTime;

	collider->Transform(position);
}

void Transform::Rotate(float angle) const
{
	rotation->x = sin(angle);
	rotation->z = -cos(angle);
}

void Transform::update(float deltaTime)
{
	if (gravity == 1) {
		velocity.y += _gravity_vec->y * deltaTime;
		position->y += velocity.y * deltaTime;
#if _WITHOUT_TERRAIN_COLLISIONS 1
		if (position->y <= OFFSET) {
			position->y = OFFSET;
		}
#endif
	}
}

void Transform::isColliding(BoxCollider* collider) const
{
	if(this->collider->Intersects(collider)) {
		this->position->x = this->position->x - (0.1f * rotation->x);
		this->position->z = this->position->z - (0.1f * rotation->z);
	}
}
