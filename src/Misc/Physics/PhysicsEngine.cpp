#include "PhysicsEngine.h"
#include "IntersectData.h"
#include "PhysicsObject.h"

RigidBody& PhysicsEngine::moveObject()
{
	if(m_objects.size() != 0)
		return m_objects[0].getRigidBody();
	return RigidBody(0);
}

void PhysicsEngine::AddObject(const PhysicsObject& body)
{
	m_objects.push_back(body);
}

void PhysicsEngine::Simulate(float deltaTime)
{
	for (size_t i = 0; i < GetNumObjects(); i++)
	{
		m_objects[i].Simulate(deltaTime);
	}
}

void PhysicsEngine::HandleCollisions()
{
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		for (auto x = i + 1; x < m_objects.size(); x++)
		{
			auto intersect_data = m_objects[i].getCollider().Intersect(m_objects[x].getCollider());

			if(intersect_data.GetDoesIntersect())
			{
				auto direction = intersect_data.GetDirection().Normalized();
				auto otherDirection = vec::Vector3::Reflect(direction, m_objects[i].getVelocity());
				m_objects[i].setForce(m_objects[i].getVelocity().Reflect(otherDirection));
				m_objects[x].setForce(m_objects[x].getVelocity().Reflect(direction));
			}
		}
	}
}
