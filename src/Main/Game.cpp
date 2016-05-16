#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include <Misc/Lights/Lightning.h>
#include "Space/Planets/SolarSystem.h"
#include "Mouse/Mouse.h"
#include "Camera/FPScamera.h"
#include "Main/GameMain.h"

#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_                  1

Game* Game::instance = nullptr;
GameTime* Game::gameTime = new GameTime();
GLuint Game::EvenFlag = 0;

GLuint GLUT_WINDOW0_ID = 0;
GLuint GLUT_WINDOW1_ID = 0;

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	cout << "Game Initialized\n";
}

Game::~Game()
{
	delete gameTime;
	cout << "\nClosed";
}

int Game::start(int windowHeigth, int windowWidth, string windowTitle)
{
	glutInitWindowSize(windowWidth, windowHeigth);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	GLUT_WINDOW0_ID = glutCreateWindow(windowTitle.c_str());

	//Initialize variables
	init();

	glutMainLoop();

	return 0;
}

void Game::init()
{
	MainGame::Initialize();

	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutReshapeFunc(resize);

	glutKeyboardFunc(Keyboard::keydoardCallback);
	glutKeyboardUpFunc(Keyboard::keyboardUpCallback);
	glutPassiveMotionFunc(Mouse::passiveMouseFunc);

	MainGame::Load();
}

void Game::resize(int width, int height)
{
	float ratio;
	if (height == 0) height = 1;
	ratio = 1.0 * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, ratio, 0.01, INFINITE);
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthRange(0.0, 0.5);
	glDepthFunc(GL_LESS);
	EvenFlag = 1;
	glMatrixMode(GL_MODELVIEW);
}

void Game::Update()
{
	gameTime->start(glutGet(GLUT_ELAPSED_TIME) * 0.001);

	MainGame::Load();

	glutPostRedisplay();
}

GLvoid Game::render()
{
	if(EvenFlag) {
		glDepthFunc(GL_LESS);
		glDepthRange(0.0, 0.5);
	}
	else{
		glDepthFunc(GL_GREATER);
		glDepthRange(1.0, 0.5);
	}
	EvenFlag = !EvenFlag;

	MainGame::Draw();

	//#if _DEBUG_ 1
	//	auto fps = "FPS: " + to_string(gameTime->getFps());
	//	text->drawText(fps);
	//#endif
	glutSwapBuffers();	
	gameTime->end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}

