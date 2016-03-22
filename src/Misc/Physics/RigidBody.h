#pragma once
#include "../../Vars/vec3f.h"
#include "Mesh/BoxShape.h"

#define GRAVITY     -9.8

class BoxShape;

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
	vec::Vector3 orientation;
	/*Linear Velocity of the rigidBody*/
	vec::Vector3 velocity;
	/*Angular velocity or rotation of the rigidBody*/
	vec::Vector3 rotation;
	vec::Vector3 torque;
	float angle;
	BoxShape shape;
	vec::Vector3 force;

	//Falling Properties
	vec::Vector3 down_force_ = vec::Vector3(0.0, 0.0, 0.0);
	vec::Vector3 gravity = vec::Vector3(0.0, GRAVITY, 0.0);
	bool isFalling = false;
	float fallTime = 0;
	//end falling properties

	float atrt;

	explicit RigidBody(float mass_x);
	~RigidBody();

	BoxShape getShape() const;
	void computeAuxiliary(float deltaTime);
	void calculateTorque();
	void calculateForces(float deltaTime);
	void initializeRigidBodies(vec::Vector3 &pos);
	void resetForces();
	void Update(float deltaTime);
	/**
	* Adds the given force to the center of mass of the rigid body.
	* The force is expressed in world coordinates.
	*/
	void addForce(const vec::Vector3 &force);
};

