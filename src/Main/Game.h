#include <string>
#include "../Misc/RenderText.h"
#include "../Vars/GameTime.h"
#include "UniverseSimulator.h"
#include "Camera/SimpleCamera.h"
#include "Space/Planets/SolarSystem.h"

#pragma once

#define _640_BY_480_RR_60   "640x480:32@60"
#define _640_BY_480_	    "640x480:32"
#define _800_BY_600_RR_60   "800x600:32@60"
#define _800_BY_600			"800x600:32"
#define _1366_BY_768_RR_60  "1366x768:32@60"
#define _1366_BY_768		"1366x768:32"
#define _1920_BY_1080_RR_60	"1920x1080:32@60"
#define _1920_BY_1080		"1920x1080:32"

class Game
{
public:

	enum GameState
	{
		Menu,
		InGame,
		Exiting
	};

	static GameState state;

	static Game * getInstance(int argc, char **argv) {
		if (instance == nullptr) {
			instance = new Game(argc, argv);
		}
		return instance;
	}

	static int start(int windowHeigth, int windowWidth, std::string windowTitle);

	static UniverseSimulator* universe;
	static SolarSystem* solarSystem;
	static SolarSystem* solarSystem_1;
	static SimpleCamera* m_camera;
	static void init();
private:
	Game(int argc, char **argv);
	~Game();

	static void resize(int width, int height);
	static void Update();
	static void render();

	static void AddItems();

	static Game* instance;
	static RenderText* text;
	static RenderText* m_text1;
	static GameTime gameTime;
};

