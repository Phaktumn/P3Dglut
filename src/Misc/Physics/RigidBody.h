#pragma once
#include "../../Vars/vec3f.h"
#include "../../Vars/Quaternion/Quaternion.h"

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

	Matrix::Matrix4 transformMatrix;
	
	/**
	* Holds the inverse of the body’s inertia tensor. The inertia
	* tensor provided must not be degenerate (that would mean
	* the body had zero inertia for spinning along one axis).
	* As long as the tensor is finite, it will be invertible.
	* The inverse tensor is used for similar reasons as those
	* for the use of inverse mass.
	*
	* The inertia tensor, unlike the other variables that define
	* a rigid body, is given in body space.
	*
	* @see inverseMass
	*/
	Matrix::Matrix3 inverseInertiaTensor;
	Matrix::Matrix3 inverseInertiaTensorWorld;
	vec::Vector3 forceAccum;
	RigidBody();
	~RigidBody();

	void integrate(float duration);
	void clearAccumulators();
	void setInertiaTensor(const Matrix::Matrix3 &inertiaTensor);

	/**
	* Adds the given force to the center of mass of the rigid body.
	* The force is expressed in world coordinates.
	*
	* @param force The force to apply.
	*/
	void addForce(const vec::Vector3 &force);

	/** JUST TO MAKE SURE I KNOW WTF IS THIS!!!!!!!!!!!!
	* Calculates internal data from state data. This should be called
	* after the body’s state is altered directly (it is called
	* automatically during integration). If you change the body’s
	* state and then intend to integrate before querying any data
	* (such as the transform matrix), then you can omit this step.
	*/
	void calculateDerivedData();

private:
	void _calculateTranformMatrix(Matrix::Matrix4 &tranform_matrix4,
		const vec::Vector3 &pos, const Quaternion &orientation);
	/**
	* Internal function to do an inertia tensor transform by a quaternion.
	*/
	static void _transformInertiaTensor(Matrix::Matrix3 &iitWorld,
		const Quaternion &q, const Matrix::Matrix3 &iitBody, const Matrix::Matrix4 &rotmat);
	static void _checkInverseInertiaTensor(Matrix::Matrix3 matrix3);
};

