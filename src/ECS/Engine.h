#pragma once
#include <vector>
#include <memory>
#include "System.h"

namespace p3d
{
	class EntityFactory;
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Initialize();
		void Update();
		void Render();
		void Dispose();

		System* AddSystem(System* system);

	private:
		std::vector<std::unique_ptr<System>> systems;
		EntityFactory* entityFactory;
	};
}
