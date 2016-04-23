#pragma once

namespace p3d
{
	class Entity
	{
		friend class EntityFactory;

	public:
		Entity(int id)
			: id(id), mask(0), alive(true)
		{
		}

		~Entity() { }

		int getId() const {
			return id;
		}

		long getMask() const
		{
			return mask;
		}

		bool isAlive() const
		{
			return alive;
		}

	private:
		const int id;
		long mask;
		bool alive;
	};
}