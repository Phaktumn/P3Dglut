#include "PhysicsObject.h"
#include "Mesh/AABB.h"
#define OFFSET 0.3

PhysicsObject::PhysicsObject(vec::Vector3& pos)
{
	m_collider = new AABB(vec::Vector3(0, 0, 0), vec::Vector3(2, 1, 1));
	m_collider->AddReference();
	m_position = pos;
	m_rotation = vec::Vector3::zero();
	rigidBody->initializeRigidBodies(m_position);
	rigidBody->addForce(vec::Vector3(0, 0, 0));
}

PhysicsObject::PhysicsObject(vec::Vector3& pos, Collider& collider)
{
	m_collider = &collider;
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
		m_collider->Tranform(m_position);
		m_Force = rigidBody->force;
	}
}

vec::Vector3 PhysicsObject::getPosition() {
	m_position = rigidBody->position;
	return  m_position;
}

vec::Vector3 PhysicsObject::getRotation() {
	m_rotation = rigidBody->orientation;
	return m_rotation;
}

vec::Vector3 PhysicsObject::getVelocity() {
	m_velocity = rigidBody->velocity;
	return m_velocity;
}

bool PhysicsObject::isKinematic() const
{
	return Kinematic;
}

void PhysicsObject::setKinematic(bool state)
{
	Kinematic = state;
}

RigidBody& PhysicsObject::getRigidBody() const
{
	return *rigidBody;
}

void PhysicsObject::setForce(vec::Vector3& force)
{
	m_Force = force;
}
