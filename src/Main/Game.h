#include <string>
#include "../Misc/RenderText.h"
#include "../Vars/Object.h"
#include "../Vars/dL/DisplayList.h"
#include "../Misc/Lights/Lightning.h"
#include "Player/Player.h"
#include "../Vars/GameTime.h"
#include "../Misc/Physics/PhysicsEngine.h"
#include "../Misc/Physics/Mesh/Plane.h"
#pragma once

class Game
{
public:
	static Game * getInstance(int argc, char **argv) {
		if (instance == nullptr) {
			instance = new Game(argc, argv);
		}
		return instance;
	}

	int start(int windowHeigth, int windowWidth, std::string windowTitle) const;

	static Camera* m_camera;
private:
	Game(int argc, char **argv);
	~Game();

	static void resize(int width, int height);
	static void Update();
	static void render();

	static Game* instance;
	static RenderText text;
	static GameTime gameTime;
};

