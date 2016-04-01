#pragma once
#include <vector>
#include "Entity.h"
#include "Component.h"
#include <typeindex>
#include <unordered_map>

namespace p3d
{
	class EntityFactory
	{
		friend class Engine;

	public:
		EntityFactory();

		static EntityFactory* getInstance();
		void Dispose() const;
		
		Entity* CreateEntity();
		Entity* GetEntity(long id);

		Component* AddComponent(Entity* entity, Component* component);

		template <typename T>
		T* GetComponent(long id);

		template <typename T>
		T* GetComponent(Entity* entity);

	private:
		~EntityFactory();

		static EntityFactory* instance;

		long entityCount;
		std::vector<Entity*> entities;
		std::vector<Entity*> addedEntities;
		std::unordered_map<long, std::unordered_map<std::type_index, Component*>> components;
	};

	template <typename T>
	T* EntityFactory::GetComponent(long id)
	{
		return dynamic_cast<T*>(components[id][std::type_index(typeid(T))]);
	}

	template <typename T>
	T* EntityFactory::GetComponent(Entity* entity)
	{
		return GetComponent<T>(entity->getId());
	}
}

