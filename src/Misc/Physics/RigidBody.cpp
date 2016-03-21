#include "RigidBody.h"



RigidBody::RigidBody(): inverseMass(0), angle(0)
{
	shape = BoxShape();
}


RigidBody::~RigidBody()
{

}

void RigidBody::initializeRigidBodies(vec::Vector3 &pos, float mass)
{
	this->position = pos;
	this->velocity = vec::Vector3(0, 0, 0);
	this->rotation = vec::Vector3(0, 0, 0);

	//MASS TEST FOR PORSCHE
	shape.mass = mass;
	shape.width = 2;
	shape.height = 1;
	shape.depth = 2;
	BoxShape::calculateBoxInertia(&shape);
	this->shape = shape;
}

void RigidBody::addForce(const vec::Vector3& force)
{
	//applies force at a point in the body
	auto _force = vec::Vector3(force.x, GRAVITY + force.y, force.z);
	this->force = _force;
	auto pointOfActuation =
		vec::Vector3(shape.width / 2, shape.height / 2, shape.depth / 2);
	vec::Vector3 cross;
	cross.x = pointOfActuation.y*_force.z - pointOfActuation.z*_force.y;
	cross.y = pointOfActuation.z*_force.x - pointOfActuation.x*_force.z;
	cross.z = pointOfActuation.x*_force.y - pointOfActuation.y*_force.x;
	this->torque = cross;
}
