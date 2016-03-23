#include "Movement.h"


Transform::Transform(): mass(1250)
{
	position = vec::Vector3(0, 1, 0);
	rotation = vec::Vector3(0, 0, 0);
	linearRot = vec::Vector3::zero();
	Force = vec::Vector3::zero();
	gravity = 1; //1 = activado 0 = desativado
	collider = new SphereCollider(&position, 2);
	body = new RigidBody(mass);
	body->initializeRigidBodies(this->position);
	body->addForce(vec::Vector3(0, 0, 0));
}


Transform::~Transform()
{

}

void Transform::Move(float x) const
{
	body->addForce(vec::Vector3(x, 0.0, x));
}

void Transform::Rotate(float angle) const
{
	body->rotate(angle);
}

void Transform::update(float deltaTime)
{
	if (gravity == 1) {
		body->Update(deltaTime);	
		this->rotation = body->orientation;
		body->orientation.y = 1;
		this->linearRot = body->rotation;
		this->position = body->position;
#if _WITHOUT_TERRAIN_COLLISIONS 1
		if (position.y <= OFFSET) {
			body->velocity.y = 0;
			body->rotation = vec::Vector3::zero();
			position.y = OFFSET;
		}
#endif
	}
}
