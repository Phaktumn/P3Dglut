#include <string>
#include "../Misc/RenderText.h"
#include "../Vars/GameTime.h"
#include "Camera/StaticCamera.h"
#include "MainMenu.h"
#include "Planets/SolarSystem.h"
#pragma once

#define _640_BY_480_RR_60   "640x480:32@60"
#define _640_BY_480_	    "640x480:32"
#define _800_BY_600_RR_60   "800x600:32@60"
#define _800_BY_600			"800x600:32"
#define _1366_BY_768_RR_60  "1366x768:32@60"
#define _1366_BY_768		"1366x768:32"

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

	int start(int windowHeigth, int windowWidth, std::string windowTitle) const;

	static SolarSystem* solarSystem;
	static StaticCamera* m_camera;
	static void init();
private:
	Game(int argc, char **argv);
	~Game();

	static void resize(int width, int height);
	static void Update();
	static void render();

	static Game* instance;
	static RenderText* text;
	static RenderText* m_text1;
	static GameTime gameTime;
};

