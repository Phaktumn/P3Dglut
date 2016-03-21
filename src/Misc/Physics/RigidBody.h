#pragma once
#include "../../Vars/vec3f.h"
#include "../../Vars/Quaternion/Quaternion.h"
#include "../../Vars/Mesh/BoxShape.h"

#define GRAVITY     -9.8

namespace vec{
	class Vector3;
}

class RigidBody
{
public:
	/*Inverse of the mass of the rigidBody*/
	float inverseMass;
	/*Linear Position in World*/
	vec::Vector3 position;
	/*Angular Orientation*/
	Quaternion orientation;
	/*Linear Velocity of the rigidBody*/
	vec::Vector3 velocity;
	/*Angular velocity or rotation of the rigidBody*/
	vec::Vector3 rotation;
	vec::Vector3 torque;
	float angle;
	BoxShape shape;
	vec::Vector3 force;

	float atrt;

	explicit RigidBody();
	~RigidBody();

	void computeAuxiliary();
	void calculateTorque();
	void calculateForces(float deltaTime);
	void initializeRigidBodies(vec::Vector3 &pos, float mass);
	void resetForces();
	void Update(float deltaTime);
	/**
	* Adds the given force to the center of mass of the rigid body.
	* The force is expressed in world coordinates.
	*/
	void addForce(const vec::Vector3 &force, float deltaTime);
};

