#include "RigidBody.h"



RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::integrate(float duration)
{
	clearAccumulators();
}

void RigidBody::clearAccumulators()
{
}

void RigidBody::setInertiaTensor(const Matrix::Matrix3& inertiaTensor)
{
	inverseInertiaTensor.setInverse(inertiaTensor);
	_checkInverseInertiaTensor(inverseInertiaTensor);
}

void RigidBody::addForce(const vec::Vector3& force)
{
	forceAccum += force;
}

void RigidBody::calculateDerivedData()
{
	_calculateTranformMatrix(transformMatrix, position, orientation);
	_transformInertiaTensor(inverseInertiaTensorWorld, orientation,
		inverseInertiaTensor, transformMatrix);
}

void RigidBody::_calculateTranformMatrix(Matrix::Matrix4& tranform_matrix4, 
	const vec::Vector3& pos, const Quaternion& orientation)
{
	transformMatrix.data[0] = 1 - 2 * orientation.y * orientation.y -
		2 * orientation.z * orientation.z;
	transformMatrix.data[1] = 2 * orientation.x * orientation.y -
		2 * orientation.w * orientation.z;
	transformMatrix.data[2] = 2 * orientation.x * orientation.z +
		2 * orientation.w * orientation.y;
	transformMatrix.data[3] = position.x;
	transformMatrix.data[4] = 2 * orientation.x * orientation.y +
		2 * orientation.w * orientation.z;
	transformMatrix.data[5] = 1 - 2 * orientation.x * orientation.x -
		2 * orientation.z * orientation.z;
	transformMatrix.data[6] = 2 * orientation.y * orientation.z -
		2 * orientation.w * orientation.x;
	transformMatrix.data[7] = position.y;
	transformMatrix.data[8] = 2 * orientation.x * orientation.z -
		2 * orientation.w * orientation.y;
	transformMatrix.data[9] = 2 * orientation.y * orientation.z +
		2 * orientation.w * orientation.x;
	transformMatrix.data[10] = 1 - 2 * orientation.x * orientation.x -
		2 * orientation.y * orientation.y;
	transformMatrix.data[11] = position.z;
}

void RigidBody::_transformInertiaTensor(Matrix::Matrix3& iitWorld, 
	const Quaternion& q, const Matrix::Matrix3& iitBody, const Matrix::Matrix4& rotmat)
{
	float t4 = rotmat.data[0] * iitBody.data[0] +
		rotmat.data[1] * iitBody.data[3] +
		rotmat.data[2] * iitBody.data[6];
	float t9 = rotmat.data[0] * iitBody.data[1] +
		rotmat.data[1] * iitBody.data[4] +
		rotmat.data[2] * iitBody.data[7];
	float t14 = rotmat.data[0] * iitBody.data[2] +
		rotmat.data[1] * iitBody.data[5] +
		rotmat.data[2] * iitBody.data[8];
	float t28 = rotmat.data[4] * iitBody.data[0] +
		rotmat.data[5] * iitBody.data[3] +
		rotmat.data[6] * iitBody.data[6];
	float t33 = rotmat.data[4] * iitBody.data[1] +
		rotmat.data[5] * iitBody.data[4] +
		rotmat.data[6] * iitBody.data[7];
	float t38 = rotmat.data[4] * iitBody.data[2] +
		rotmat.data[5] * iitBody.data[5] +
		rotmat.data[6] * iitBody.data[8];
	float t52 = rotmat.data[8] * iitBody.data[0] +
		rotmat.data[9] * iitBody.data[3] +
		rotmat.data[10] * iitBody.data[6];
	float t57 = rotmat.data[8] * iitBody.data[1] +
		rotmat.data[9] * iitBody.data[4] +
		rotmat.data[10] * iitBody.data[7];
	float t62 = rotmat.data[8] * iitBody.data[2] +
		rotmat.data[9] * iitBody.data[5] +
		rotmat.data[10] * iitBody.data[8];
	iitWorld.data[0] = t4 * rotmat.data[0] +
		t9 * rotmat.data[1] +
		t14 * rotmat.data[2];
	iitWorld.data[1] = t4 * rotmat.data[4] +
		t9 * rotmat.data[5] +
		t14 * rotmat.data[6];
	iitWorld.data[2] = t4 * rotmat.data[8] +
		t9 * rotmat.data[9] +
		t14 * rotmat.data[10];
	iitWorld.data[3] = t28 * rotmat.data[0] +
		t33 * rotmat.data[1] +
		t38 * rotmat.data[2];
	iitWorld.data[4] = t28 * rotmat.data[4] +
		t33 * rotmat.data[5] +
		t38 * rotmat.data[6];
	iitWorld.data[5] = t28 * rotmat.data[8] +
		t33 * rotmat.data[9] +
		t38 * rotmat.data[10];
	iitWorld.data[6] = t52 * rotmat.data[0] +
		t57 * rotmat.data[1] +
		t62 * rotmat.data[2];
	iitWorld.data[7] = t52 * rotmat.data[4] +
		t57 * rotmat.data[5] +
		t62 * rotmat.data[6];
	iitWorld.data[8] = t52 * rotmat.data[8] +
		t57 * rotmat.data[9] +
		t62 * rotmat.data[10];
}

void RigidBody::_checkInverseInertiaTensor(Matrix::Matrix3 matrix3)
{

}
