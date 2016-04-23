#include "EntityFactory.h"
#include "TypeMapper.h"

namespace p3d
{
	EntityFactory* EntityFactory::instance;

	EntityFactory* EntityFactory::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new EntityFactory();
		}

		return instance;
	}

	EntityFactory::EntityFactory(): entityCount(0)
	{
	}

	EntityFactory::~EntityFactory()
	{
		entities.clear();
	}

	void EntityFactory::Dispose() const
	{
		delete instance;
	}

	Entity* EntityFactory::CreateEntity()
	{
		entities.emplace_back(new Entity(entityCount++));
		Entity* ptr = entities.back();
		addedEntities.push_back(ptr);

		return ptr;
	}

	Entity* EntityFactory::GetEntity(long id)
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->getId() == id)
				return entities[i];
		}

		return nullptr;
	}

	Component* EntityFactory::AddComponent(Entity* entity, Component* component)
	{
		components[entity->getId()][component->getType()] = component;
		entity->mask |= getMask(component->getType());
		return component;
	}
}
