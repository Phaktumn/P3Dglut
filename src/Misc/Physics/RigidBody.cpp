#include "RigidBody.h"
#include "../../Vars/Quaternion/Quaternion.h"


RigidBody::RigidBody(float mass_x): inverseMass(0), angle(0)
{
	shape = BoxShape(mass_x);
	atrt = 0.99f;
}


RigidBody::~RigidBody()
{

}

BoxShape RigidBody::getShape() const
{
	return this->shape;
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

void RigidBody::computeAuxiliary(float deltaTime)
{
	//rotation aux
	auto angularAccelX = this->torque.x / shape.momentOfInertia.x;
	auto angularAccely = this->torque.y / shape.momentOfInertia.y;
	auto angularAccelz = this->torque.z / shape.momentOfInertia.z;
	this->rotation += vec::Vector3(angularAccelX, angularAccely, angularAccelz) * deltaTime;

	//Linear Velocity
	inverseMass = shape.getInverseMass();
	velocity = force * inverseMass;
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

void RigidBody::initializeRigidBodies(vec::Vector3 &pos)
{
	this->position = pos;
	this->velocity = vec::Vector3(0, 0, 0);
	this->rotation = vec::Vector3(1.0, 0, 1.0);

	//MASS TEST FOR PORSCHE
	shape.width = 2;
	shape.height = 1;
	shape.depth = 2;
	shape.calculateBoxInertia();
	this->shape = shape;
}

void RigidBody::resetForces()
{
	this->force = vec::Vector3::zero();
	this->torque = vec::Vector3::zero();
	this->rotation = vec::Vector3(1.0, 0.0, 1.0);
}

void RigidBody::Update(float deltaTime)
{
	if (position.y >= 0.5) isFalling = true;
	else { isFalling = false; fallTime = 0; down_force_ = gravity; }
	if(isFalling) {
		fallTime += deltaTime;
		down_force_ += gravity;
	}
	addForce(vec::Vector3(force.x, force.y, force.z) + down_force_);
	calculateTorque();
	calculateForces(deltaTime);
	computeAuxiliary(deltaTime);
	this->force *= atrt;
	if (force.x <= 0.2) force.x = 0;
	if (force.z <= 0.2) force.z = 0;
	position += velocity * orientation * deltaTime;
}

void RigidBody::addForce(const vec::Vector3& force)
{
	//applies force at a point in the body
	auto _force = vec::Vector3(force.x, force.y, force.z);
	this->force = _force;
}

void RigidBody::rotate(float angle)
{
	orientation.x = sin(angle);
	orientation.y = 1;
	orientation.z = -cos(angle);
}

