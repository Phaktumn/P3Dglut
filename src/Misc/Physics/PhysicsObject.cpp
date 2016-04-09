#include "PhysicsObject.h"

#define OFFSET 0.3

PhysicsObject::PhysicsObject(vec::Vector3 pos,
	Collider& collider) : m_collider(collider)
{
	m_collider.AddReference();
	m_position = pos;
	m_rotation = vec::Vector3::zero();
	rigidBody = new RigidBody(1000);
	rigidBody->initializeRigidBodies(m_position);
	rigidBody->addForce(vec::Vector3(0, 0, 0));
}
 
PhysicsObject::~PhysicsObject()
{

}

void PhysicsObject::Simulate(float deltaTime)
{
	if (Kinematic == false)
	{
		rigidBody->Update(deltaTime);
		m_collider.Transform(rigidBody->position);
		m_position = rigidBody->position;
		m_rotation = rigidBody->orientation;
		m_velocity = rigidBody->velocity;
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

vec::Vector3 PhysicsObject::getForce()
{
	m_Force = rigidBody->force;
	return m_Force;
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
	rigidBody->force = m_Force;
}

void PhysicsObject::setVelocity(vec::Vector3& velocity)
{
	m_velocity = velocity;
	rigidBody->velocity = m_velocity;
}

