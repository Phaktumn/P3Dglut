#include <string>
#include "../Misc/RenderText.h"
#include "../Vars/Object.h"
#include "../Vars/dL/DisplayList.h"
#include "../Misc/Physics/Movement.h"
#include "../Misc/Lights/Lightning.h"
#include "Player/Player.h"
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

	static float deltaTime;
	static char getKeyPressed(unsigned char KEY);
	static DisplayList * list1;

private:
	Game(int argc, char **argv);
	~Game();

	static void resize(int width, int height);
	static void Update();
	static void render();

	static void keyboardCallback(unsigned char KEY, int x, int y);
	static void upCallback(unsigned char KEY, int x, int y);

	static Game* instance;

	static bool KEYS[512];

	static int _INDEX;
	static float red[3];
	static float green[3];
	static float blue[3];
	static float violet[3];
	static float Colors[10][3];

	static float windowHeigth, windowWidth;

	static void move(float i);
	static void rotate(float angle);
	 
	static int font;
	static float lx, lz;
	static float posX, posY, posZ;
	static float x, y, z;
	static float rotateX, rotateY, rotateZ;
	static float rotationAngle;
	static int startTime;
	static float time;
	static int framesPS;
	static int frames;
	static float speed;
	static GLfloat lModel_ambient[];
	static RenderText* text;
	static RenderText* WTF;
	static Object* Tree;
	static BoxCollider* colliderBox;
	static Lightning * lights;
	static Player* Gamer;
};

