#include "Engine.h"
#include "EntityFactory.h"

namespace p3d
{
	Engine::Engine(): entityFactory(EntityFactory::getInstance())
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::Initialize()
	{	
		for (size_t i = 0; i < systems.size(); i++)
		{
			systems[i]->OnInitialize();
			systems[i]->engine = this;
		}
	}

	void Engine::Update()
	{
		for (size_t i = 0; i < entityFactory->addedEntities.size(); i++)
		{
			for (size_t j = 0; j < systems.size(); j++)
			{
				systems[j]->NotifyEntityAdded(entityFactory->addedEntities[i]);
			}
		}

		if (entityFactory->addedEntities.size() > 0)
			entityFactory->addedEntities.clear();

		for (size_t i = 0; i < systems.size(); i++)
		{
			systems[i]->OnUpdate();
		}
	}

	void Engine::Render()
	{
		for (size_t i = 0; i < systems.size(); i++)
		{
			systems[i]->OnRender();
		}
	}

	void Engine::Dispose()
	{
		for (size_t i = 0; i < systems.size(); i++)
		{
			systems[i]->OnDispose();
		}
	}

	System* Engine::AddSystem(System* system)
	{
		systems.push_back(std::unique_ptr<System>(system));
		return systems.back().get();
	}
}
