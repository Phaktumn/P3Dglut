#pragma once
#include <vector>

class RigidBody;
class PhysicsObject;

class PhysicsEngine
{
public:
	PhysicsEngine() {}
	~PhysicsEngine();

	void AddObject(const PhysicsObject& body);
	void Simulate(float deltaTime);

	//Move Required Object
	RigidBody& moveObject();

	void HandleCollisions();

	unsigned int GetNumObjects() const{
		return unsigned int(m_objects.size());
	}

private:
	int listFront_index = 0;
	std::vector<PhysicsObject> m_objects;
};

