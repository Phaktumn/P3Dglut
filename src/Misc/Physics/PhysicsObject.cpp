#include "PhysicsObject.h"
#define OFFSET 0.3

PhysicsObject::PhysicsObject(vec::Vector3& pos)
{
	m_collider = new Collider(Collider::TYPE_SPHERE);
	m_collider->AddReference();
	m_position = pos;
	m_rotation = vec::Vector3::zero();
	rigidBody->initializeRigidBodies(m_position);
	rigidBody->addForce(vec::Vector3(0, 0, 0));
}

PhysicsObject::~PhysicsObject()
{
	if(m_collider->RemoveReference()){
		if (m_collider) delete m_collider;
	}
}

void PhysicsObject::Simulate(float deltaTime)
{
	if (Kinematic == false)
	{
		rigidBody->Update(deltaTime);
		m_Force = rigidBody->force;
		m_rotation = rigidBody->orientation;
		m_velocity = rigidBody->velocity;
		m_position = rigidBody->position;
	}
}

RigidBody& PhysicsObject::getRigidBody() const
{
	return *rigidBody;
}
