#ifndef PHYSICS_OBJECT_INCLUDED_H
#define PHYSICS_OBJECT_INCLUDED_H

/**
* The PhysicsObject class represents an object that can be used in a physics
* engine with RigidBody.
*/
#pragma once
#include "Collider.h"
#include "../../Vars/vec3f.h"
#include "RigidBody.h"

class RigidBody;
class Collider;

class PhysicsObject
{
public:
	PhysicsObject(): m_collider(nullptr)
	{}
	explicit PhysicsObject(vec::Vector3& pos);
	~PhysicsObject();

	void Simulate(float deltaTime);

	const Collider& getCollider() { return *m_collider; }
	vec::Vector3 getPosition() const{ return m_position; }
	vec::Vector3 getRotation() const{ return m_rotation; }
	vec::Vector3 getVelocity() const { return m_velocity; }
	bool isKinematic() const{ return Kinematic; }
	void setKinematic(bool state) { Kinematic = state; }
	RigidBody& getRigidBody() const;
	void setForce(vec::Vector3& force) { m_Force = force; }

private:
	vec::Vector3 m_position;
	vec::Vector3 m_rotation;
	vec::Vector3 m_velocity;
	Collider* m_collider;
	vec::Vector3 m_Force;
	RigidBody* rigidBody = new RigidBody(1000);
	bool Kinematic = false;
};

#endif

