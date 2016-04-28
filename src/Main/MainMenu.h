#pragma once
#include "Camera/Camera.h"


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	static void start();
	static void update();
	static void draw();

private:
	static GLuint createMenu;
	static GLuint PlanetsMenu;
	static GLuint CameraOptions;
	static void menuCallback(int);
	static void menuPlanets(int);
	static void menuCamera(int);
	static void processStatus(int, int, int);
	static int menuFlag;
	static GLuint m_lastPrintIndex;
	static GLuint m_currPrintIndex;
};

