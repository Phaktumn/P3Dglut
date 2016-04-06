#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include "../Misc/Physics/Mesh/Plane.h"
#include "Planets/SolarSystem.h"
#include "Camera/StaticCamera.h"

#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_                  1

Game* Game::instance = nullptr;
GLfloat Game::lModel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
RenderText Game::text = RenderText();
RenderText Game::WTF = RenderText();
Object * Game::Tree;
DisplayList * Game::list1 = new DisplayList(3);
Lightning * Game::lights = new Lightning(1);
Player * Game::Gamer;
GameTime Game::gameTime = GameTime();
Camera* camera;
SolarSystem* solarSystem = new SolarSystem();

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	std::cout << "Game Initialized";
}

Game::~Game()
{
	delete Gamer;
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CW);
	glFrontFace(GL_CCW);

	// ReSharper disable once CppMsExtBindingRValueToLvalueReference
	camera = new StaticCamera(vec::Vector3(0, 20, 300), 0);
	solarSystem->Load();

	//224,255,255
	lights->setAmbientColor(vec::Vector3(MathHelper::normalizef(56, 255), 0, 0), 0.5);
	lights->setDiffuse(vec::Vector3(MathHelper::normalizef(189, 255)), 1);
	lights->setSpecular(vec::Vector3(125), 1);
	lights->enableLight();

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
	gluPerspective(45, ratio, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void Game::Update()
{
	gameTime.start(glutGet(GLUT_ELAPSED_TIME) * 0.001);
	camera->Update(gameTime.getDeltaTime());
	solarSystem->Simulate(gameTime.getDeltaTime());
	glutPostRedisplay();
}

GLvoid Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1.0);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.01, 1000);

	glLoadIdentity();
	glColor3f(1, 1, 1);
	camera->Draw();
	solarSystem->Draw();
	solarSystem->renderOrbits();

#if _DEBUG_ 1
	auto fps = "FPS: " + std::to_string(gameTime.getFps());
	text.drawText(fps, vec::Vector3(20, 20, 0), 0.1);
#endif
	glutSwapBuffers();	
	gameTime.end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}



