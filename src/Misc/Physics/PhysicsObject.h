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
	explicit PhysicsObject(vec::Vector3& pos, Collider& collider);
	~PhysicsObject();

	void Simulate(float deltaTime);

	const Collider& getCollider() const { return *m_collider; }

	vec::Vector3 getPosition();
	vec::Vector3 getRotation();
	vec::Vector3 getVelocity();
	bool isKinematic() const;
	void setKinematic(bool state);
	RigidBody& getRigidBody() const;
	void setForce(vec::Vector3& force);

private:
	vec::Vector3 m_position;
	vec::Vector3 m_rotation;
	vec::Vector3 m_velocity;
	vec::Vector3 m_Force;
	Collider* m_collider;
	RigidBody* rigidBody = new RigidBody(1000);
	bool Kinematic = false;
};

#endif

