#pragma once
#include <vector>
#include "RigidBody.h"

class PhysicsEngine
{
public:
	PhysicsEngine() {}
	~PhysicsEngine();

	void AddObject();
	void Simulate(float deltaTime);

	void HandleCollisions();

	unsigned int GetNumObjects() const
	{
		return unsigned int(m_objects.size());
	}

private:

	std::vector<RigidBody> m_objects;
};

