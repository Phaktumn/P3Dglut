#pragma once
#include <algorithm>
#include "../ECS/TypeMapper.h"
#include "../ECS/Entity.h"
#include "EntityFactory.h"

namespace p3d
{
	class System
	{
		friend class Engine;

	public:
		System()
			: entityFactory(EntityFactory::getInstance()), 
			engine(nullptr), 
			require(0), one(0), exclude(0) { }
		virtual ~System() { }

		virtual void OnInitialize() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnDispose() = 0;
		virtual void OnEntityAdded(Entity* entity) = 0;
		virtual void OnEntityRemoved(Entity* entity) = 0;

		template <typename T>
		void Require();

		template <typename T>
		void AtLeastOne();

		template <typename T>
		void Exclude();

	protected:
		EntityFactory* entityFactory;
		Engine* engine;
		std::vector<Entity*>& getEntities();

	private:
		long require;
		long one;
		long exclude;

		std::vector<Entity*> entities;

		void NotifyEntityAdded(Entity* entity);
		void NotifyEntityRemoved(Entity* entity);
	};

	inline std::vector<Entity*>& System::getEntities()
	{
		return entities;
	}

	inline void System::NotifyEntityAdded(Entity* entity)
	{
		long entityMask = entity->getMask();

		bool requireValid = (entityMask & require) == require;
		bool oneValid = one == 0 || (entityMask & one) != 0;
		bool excludeValid = (entityMask & exclude) == 0;

		bool valid = requireValid && oneValid && excludeValid;

		if (valid) 
		{
			entities.push_back(entity);
			OnEntityAdded(entity);
		}
	}

	inline void System::NotifyEntityRemoved(Entity* entity)
	{
		size_t size = entities.size();
		entities.erase(remove(entities.begin(), entities.end(), entity), entities.end());
		
		if (entities.size() < size)
			OnEntityRemoved(entity);
	}

	template <typename T>
	void System::Require()
	{
		long typeMask = getMask<T>();
		require |= typeMask;
	}

	template <typename T>
	void System::AtLeastOne()
	{
		long typeMask = getMask<T>();
		one |= typeMask;
	}

	template <typename T>
	void System::Exclude()
	{
		long typeMask = getMask<T>();
		exclude |= typeMask;
	}
}

