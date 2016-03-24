#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include "../Misc/Physics/Mesh/Plane.h"

#define _CRT_SECURE_NO_WARNINGS
#define _RENDER_LANDSCAPE        1
#define _RENDER_PLANE            1
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
PhysicsEngine* Game::Physics = new PhysicsEngine();
PhysicsObject* Game::ground;
Plane* Game::plane = new Plane(vec::Vector3::up(), 100);

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

	Gamer = new Player();
	Physics->AddObject(Gamer->getPhysicsObject());

	Tree = new Object("../P3Dglut/Modelos3D/rose+vase.obj");
	Tree->loadModel();

	ground = new PhysicsObject(vec::Vector3(0, 0, 0), (Collider)*plane);
	ground->setKinematic(true);
	Physics->AddObject(*ground);

	//224,255,255
	lights->setAmbientColor(vec::Vector3(MathHelper::normalizef(255, 255), 1, 1), 1);
	lights->setDiffuse(vec::Vector3(MathHelper::normalizef(255, 255)), 1);
	lights->setSpecular(vec::Vector3(255), 1);
	lights->enableLight();

	list1->GenLandScape(GL_MODELVIEW, Tree);
	list1->GenPlane(GL_QUADS, new vec::Vector3(MathHelper::normalizef(156, 255),
		MathHelper::normalizef(205, 255), MathHelper::normalizef(50, 255)));

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
	Gamer->Update(gameTime.getDeltaTime());
	Physics->Simulate(gameTime.getDeltaTime());
	Physics->HandleCollisions();
	glutPostRedisplay();
}

GLvoid Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 1.0, 1.0, 0.0);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	gluPerspective(45, glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.01, 1000);

	glLoadIdentity();
	Gamer->Draw();

#if _RENDER_LANDSCAPE 1
	glCallList(list1->getList(2));
#endif
#if _RENDER_PLANE 1
	//Desenhar plano
	glCallList(list1->getList(3));
#endif
#if _DEBUG_ 1
	auto fps = "FPS: " + std::to_string(gameTime.getFps());
	text.drawText(fps, vec::Vector3(20, 20, 0), 0.1);
#endif
	glutSwapBuffers();	
	gameTime.end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}



