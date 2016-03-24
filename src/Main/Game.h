#include <string>
#include "../Misc/RenderText.h"
#include "../Vars/Object.h"
#include "../Vars/dL/DisplayList.h"
#include "../Misc/Lights/Lightning.h"
#include "Player/Player.h"
#include "../Vars/GameTime.h"
#include "../Misc/Physics/PhysicsEngine.h"
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

	static DisplayList * list1;
private:
	Game(int argc, char **argv);
	~Game();

	static void resize(int width, int height);
	static void Update();
	static void render();

	static Game* instance;
	static GLfloat lModel_ambient[];
	static RenderText text;
	static RenderText WTF;
	static Object* Tree;
	static Lightning * lights;
	static Player* Gamer;
	static Plane* plane;
	static PhysicsObject* ground;
	static GameTime gameTime;
	static PhysicsEngine* Physics;
};

