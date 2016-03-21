#include "RigidBody.h"



RigidBody::RigidBody(): inverseMass(0), angle(0)
{
	shape = BoxShape();
}


RigidBody::~RigidBody()
{

}

void RigidBody::calculateForces(float deltaTime)
{
	torque.x = 1.0 * sin(deltaTime * 0.9 + 0.5);
	torque.y = 1.1 * sin(deltaTime * 0.5 + 0.4);
	torque.z = 1.2 * sin(deltaTime * 0.7 + 0.9);

	torque.x -= 0.2 * rotation.x;
	torque.y -= 0.2 * rotation.y;
	torque.z -= 0.2 * rotation.z;
}

void RigidBody::computeAuxiliary()
{
	//Linear Velocity
	auto m_inverse = shape.getInverseMass();
	velocity = force * m_inverse;
}

void RigidBody::calculateTorque()
{
	auto pointOfActuation = vec::Vector3(shape.width * 0.5, shape.height* 0.5, shape.depth * 0.5);
	vec::Vector3 cross;
	cross.x = pointOfActuation.y*force.z - pointOfActuation.z*force.y;
	cross.y = pointOfActuation.z*force.x - pointOfActuation.x*force.z;
	cross.z = pointOfActuation.x*force.y - pointOfActuation.y*force.x;
	torque = cross;
}

void RigidBody::initializeRigidBodies(vec::Vector3 &pos, float mass)
{
	this->position = pos;
	this->velocity = vec::Vector3(0, 0, 0);
	this->rotation = vec::Vector3(1.0, 0, 1.0);

	//MASS TEST FOR PORSCHE
	shape.mass = mass;
	shape.width = 2;
	shape.height = 1;
	shape.depth = 2;
	shape.calculateBoxInertia();
	this->shape = shape;
}

void RigidBody::resetForces()
{
	this->force = vec::Vector3(0.0, GRAVITY, 0.0);
	this->torque = vec::Vector3(0.0, 0.0, 0.0);
	this->rotation = vec::Vector3(1.0, 0.0, 1.0);
}

void RigidBody::Update(float deltaTime)
{
	calculateTorque();
	calculateForces(deltaTime);
	computeAuxiliary();
	addForce(vec::Vector3(0, 0, 0), deltaTime);
	atrt = 0.1f;
	this->force -= atrt;
	if (force.x <= 0) force.x = 0;
	if (force.y <= 0) force.y = 0;
	if (force.z <= 0) force.z = 0;
	position += velocity * deltaTime;
}

void RigidBody::addForce(const vec::Vector3& force, float deltaTime)
{
	//applies force at a point in the body
	auto _force = vec::Vector3(force.x, GRAVITY + force.y, force.z);
	this->force = _force;
}


