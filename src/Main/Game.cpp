#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include "Planets/SolarSystem.h"
#include <Misc/Lights/Lightning.h>

#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_                  1

Game* Game::instance = nullptr;
RenderText Game::text = RenderText();
GameTime Game::gameTime = GameTime();
StaticCamera* Game::m_camera;
SolarSystem* solarSystem = new SolarSystem();

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	std::cout << "Game Initialized";
}

Game::~Game()
{
	std::cout << "Closed";
}

int Game::start(int windowHeigth, int windowWidth, std::string windowTitle) const
{
	glutInitWindowSize(windowWidth, windowHeigth);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(windowTitle.c_str());
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutReshapeFunc(resize);
	glutKeyboardFunc(Keyboard::keydoardCallback);
	glutKeyboardUpFunc(Keyboard::keyboardUpCallback);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ReSharper disable once CppMsExtBindingRValueToLvalueReference
	m_camera = new StaticCamera(vec::Vector3(0,0,0), 0.0f);
	solarSystem->Load();
	Lightning::enableLight();
	glutMainLoop();
	return 0;
}

void Game::resize(int width, int height)
{
	float ratio;
	if (height == 0) height = 1;
	ratio = 1.0 * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, ratio, 0.01, 15000);
	glMatrixMode(GL_MODELVIEW);
}

void Game::Update()
{
	gameTime.start(glutGet(GLUT_ELAPSED_TIME) * 0.001);
	solarSystem->preCameraTranslateDraw();
	m_camera->Update(gameTime.getDeltaTime());
	solarSystem->Simulate(gameTime.getDeltaTime());
	glutPostRedisplay();
}

GLvoid Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	m_camera->Draw();
	Lightning::applyLights();
	solarSystem->Draw();
	solarSystem->renderOrbits();
#if _DEBUG_ 1
	auto fps = "FPS: " + std::to_string(gameTime.getFps());
	// ReSharper disable once CppMsExtBindingRValueToLvalueReference
	text.drawText(fps, vec::Vector3(20, 20, 0), 0.1);
#endif
	glutSwapBuffers();	
	gameTime.end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}



