#pragma once

#include <string>
#include "../Misc/RenderText.h"
#include "../Vars/GameTime.h"
#include "UniverseSimulator.h"
#include "Camera/SimpleCamera.h"
#include "Space/Planets/SolarSystem.h"
#include "MainMenu.h"
#include <Misc/MiniMap.h>

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
	static Camera* m_camera;
	static Camera* orbitCamera;
	static MainMenu* menu;
	static void init();

	static void setActiveCamera(const int _index){
		cameraIndex = _index;
		cameraIndex = MathHelper::Clampf(cameraIndex, 0, 1);
	}
	static int cameraIndex;
private:
	Game(int argc, char **argv);
	~Game();

	static void resize(int width, int height);
	static void Update();
	static void render();

	static void AddItems();

	static GLuint entryMenuTexture;

	static MiniMap* m_miniMap;
	static GLUquadric* m_Object;
	static Game* instance;
	static RenderText* text;
	static GameTime* gameTime;
	static GLuint EvenFlag;
};


