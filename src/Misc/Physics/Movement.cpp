#include "Movement.h"


Transform::Transform(): mass(1250)
{
	position = vec::Vector3(0, 100, 0);
	rotation = vec::Vector3(0, 0, 0);
	linearRot = vec::Vector3::zero();
	Force = vec::Vector3::zero();
	gravity = 1; //1 = activado 0 = desativado
	collider = new SphereCollider(&position, 2);
	body = new RigidBody();
	body->initializeRigidBodies(this->position, 0.7);
	body->addForce(vec::Vector3(0, 0, 0), 0.01);
}


Transform::~Transform()
{

}

void Transform::Move(float x, float y, float z, float deltaTime)
{
	body->addForce(vec::Vector3(x * rotation.x, y, z*rotation.z), deltaTime);
}

void Transform::Rotate(float angle)
{
	rotation.x = sin(angle);
	rotation.z = -cos(angle);
}

void Transform::update(float deltaTime)
{
	if (gravity == 1) {
		body->Update(deltaTime);
		auto angularAccelX = body->torque.x / body->shape.momentOfInertia.x;
		auto angularAccely = body->torque.y / body->shape.momentOfInertia.y;
		auto angularAccelz = body->torque.z / body->shape.momentOfInertia.z;
		body->rotation += vec::Vector3(angularAccelX, angularAccely, angularAccelz) * deltaTime;	
		this->position = body->position;
		this->linearRot = body->rotation;
#if _WITHOUT_TERRAIN_COLLISIONS 1
		if (position.y <= OFFSET) {
			body->velocity.y = 0;
			body->rotation = vec::Vector3::zero();
			position.y = OFFSET;
		}
#endif
	}
}

void Transform::isColliding(BoxCollider* collider)
{
#if COLLISIONS_ENABLED 1	
	if (this->collider->Intersects(collider)) {
		this->position.x = this->position.x - (0.1f * rotation.x);
		this->position.z = this->position.z - (0.1f * rotation.z);
	}

#endif
}
